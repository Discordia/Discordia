#include "NSEWaterSolver.h"

namespace Discordia
{
	namespace Physic
	{

		// Physical parameters important to the simulation
		const f32 FLUID_DENSITY		=  1.0f;			// The density of the fluid
		const f32 GRAVITATION		=  0.1f;			// Gravitational force
		const f32 PIPE_LENGTH		=  5.0f;			// Length of a virtual connection pipe
		const f32 PIPE_AREA			=  0.0007f;			// The cross-sectional area of a pipe
		const f32 TIMESTEP			=  0.5f;			// Timestep for the integrator
		const f32 DAMPING			=  0.9997f;			// Acceleration damping factor
		const f32 INITIAL_VOLUME	=  0.001f;			// Initial volume of the water body

		NSEWaterSolver::NSEWaterSolver(const Vector2i& tesslation, const f32& hscale, f32 *heightMap)
		{
			int a;

			// Set the water surface dimensions and area
			xSize = tesslation.x;
			ySize = tesslation.y;
			area = xSize * ySize;
			columnArea = 1.0f / area;
			heightScale = hscale;

			// The column height points to the user supplied heightfield, 
			// but we also need to keep track
			// of the column volume. Get memory to store it.
			columnHeight = heightMap;
			columnVolume = new f32[area];

			// Allocate memory for the grid of virtual pipes 
			// (four types: vertical, horizontal, left diagonal, right diagonal).
			vPipes = new f32[area + xSize]; 
			hPipes = new f32[area + ySize];
			lPipes = new f32[(xSize + 1) * (ySize + 1)];
			rPipes = new f32[(xSize + 1) * (ySize + 1)];

			// All pipes have an initial flow of zero.
			for( a = 0; a < (ySize + 1) * xSize; a++ ) 
				vPipes[a] = 0.0f;

			for( a = 0; a < (xSize + 1) * ySize; a++ ) 
				hPipes[a] = 0.0f;

			for( a = 0; a < (xSize+1) * (ySize+1); a++ ) 
				lPipes[a] = rPipes[a] = 0.0f;

			// We need to uniformly distribute the initial volume of water over the column grid
			for( a = 0; a < area; a++ ) 
				columnVolume[a] = INITIAL_VOLUME / area;

			// Compute often used constant factors: acceleration factor, and force factor
			constAccel = (TIMESTEP * PIPE_AREA * GRAVITATION) / (PIPE_LENGTH * columnArea);
			constForce = (TIMESTEP * PIPE_AREA) / (PIPE_LENGTH * FLUID_DENSITY);
		}

		NSEWaterSolver::~NSEWaterSolver()
		{
			// Free column volume grid
			delete[] columnVolume;

			// Free virtual pipe grids
			delete[] vPipes;
			delete[] hPipes;
			delete[] lPipes;
			delete[] rPipes;
		}

		void NSEWaterSolver::Simulate()
		{
			ComputePipeFlows();
			UpdateVolumes();
		}

		void NSEWaterSolver::ApplyForce(s32 x, s32 y, f32 magnitude)
		{
			s32 xsp = xSize + 1;

			// Compute the total flow resulting from the applied force
			f32 p = -magnitude * constForce;

			// We can now distribute this flow over the pipes around the point of impact
			// The distribution is symmetrical to ensure volume conservation.
			hPipes[y*xsp + x]			+= p;
			vPipes[y*xSize + x]			+= p;
			lPipes[y*xsp + x]			+= p;
			rPipes[y*xsp + x + 1]		+= p;
			hPipes[y*xsp + x + 1]		-= p;
			vPipes[(y+1)*xSize + x]		-= p;
			lPipes[(y+1)*xsp + x + 1]	-= p;
			rPipes[(y+1)*xsp + x]		-= p;
		}

		void NSEWaterSolver::ComputePipeFlows()
		{
			s32 a, b, x, y;
			s32 xsp = xSize + 1;

			// Update the water flow in the horizontal virtual pipes, ...
			for( a = b = 1, y = 0; y < ySize; y++, a += 2, b++ )
				for( x = 1; x < xSize; x++, a++, b++ )
					hPipes[a] = (hPipes[a] + constAccel*(columnVolume[b-1] - columnVolume[b]))*DAMPING;

			// ... the vertical ones, ...
			for( a = xSize; a < area; a++ )
				vPipes[a] = (vPipes[a] + constAccel*(columnVolume[a-xSize] - columnVolume[a])) * DAMPING;

			// ... and finally, the left / right diagonal ones.
			for( a = xsp + 1, b = xsp, y = 1; y < ySize; y++, a += 2, b++ )
				for( x = 1; x < xSize; x++, a++, b++ ) {
					lPipes[a] = (lPipes[a] + constAccel*(columnVolume[b-xsp] - columnVolume[b])) * DAMPING;
					rPipes[a] = (rPipes[a] + constAccel*(columnVolume[b-xSize] - columnVolume[b-1])) * DAMPING;
				}
		}

		void NSEWaterSolver::UpdateVolumes()
		{
			s32 a, b, x, y;
			s32 xsp = xSize + 1;

			// Recompute the volume of all columns, using the new pipe flow values.
			// Negative volumes can result from our approximative model, 
			// clamp them to zero, and record the global error term
			f32 dist = 0.0;        
			f32 *cv = columnVolume;

			for( a = b = y = 0; y < ySize; y++, a++ ) 
			{		
				for( x = 0; x < xSize; x++, a++, b++, cv++ ) 
				{
					*cv += TIMESTEP * (hPipes[a] - hPipes[a+1] + vPipes[b] - vPipes[b+xSize] + lPipes[a] - lPipes[a+xsp+1] + rPipes[a+1] - rPipes[a+xsp]);

					if( *cv < 0 ) 
					{
						dist += *cv; 
						*cv = 0; 
					}
				}
			}

			// In the update step above, the system lost water due to the clamped negative volumes. 
			// The amount of lost volume was recorded in [dist]. We will now uniformly distribute 
			// this volume over the grid, in order to guarantee volume conservation.
			// At the same time (we combine both steps for performance reasons), we update the 
			// heightfield by dividing the volume of each column by its base area.
			float d = dist / area;
			float amp = heightScale / columnArea;
			cv = columnVolume;

			for( a = 0; a < area; a++, cv++ ) 
			{
				*cv += d;
				columnHeight[a] = (*cv) * amp;
			}
		}
	}
}