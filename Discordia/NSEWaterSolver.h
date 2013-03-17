#ifndef NSE_WATER_SOLVER_H_INCLUDED
#define NSE_WATER_SOLVER_H_INCLUDED

#include "Vector2.h"

namespace Discordia
{
	namespace Physic
	{
		/**
		 * This code is derived from Yann Lomards NSE water solver
		 * Reference: http://membres.lycos.fr/ylmb/source/solver.h
		 *			  http://membres.lycos.fr/ylmb/source/solver.cpp
		 */
		class NSEWaterSolver
		{
		public:
			NSEWaterSolver(const Vector2i& tesslation, const f32& hscale, f32 *heightMap);
			~NSEWaterSolver();

			void	Simulate();
			void	ApplyForce(s32 x, s32 y, f32 magnitude);

		private:
			void	ComputePipeFlows();
			void	UpdateVolumes();

		private:
			s32 xSize;
			s32 ySize;
			s32	area;
			f32 columnArea;
			f32 heightScale;
			f32 constAccel;
			f32 constForce;

			f32* columnHeight;
			f32* columnVolume;

			f32* vPipes;
			f32* hPipes;
			f32* lPipes;
			f32* rPipes;
		};
	}
}

#endif