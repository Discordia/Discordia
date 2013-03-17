#include "NSEHeightmapWater.h"
#include "Color.h"

#ifdef WIN32
#pragma	warning( disable : 4288)
#endif

namespace Discordia
{
	namespace Scene
	{
		NSEHeightmapWater::NSEHeightmapWater(ISceneNode* parent, const Matrix4& localTransform, const Dimension2D<s32>& dim, const f32& hscale, const Vector2i& tesslation)
			: IGeometryNode(parent, localTransform), dimension(dim), heightScale(hscale), tesslation(tesslation)
		{
			// Create heightMap and normalMap
			s32 hpLength = (tesslation.x+1)*(tesslation.y+1);
			heightMap = new f32[hpLength];

			// Init heightMap to hscale
			for (s32 i = 0; i < hpLength; i++)
				heightMap[i] = heightScale;
		
			// Create NSEWaterSolver
			waterSolver = new Physic::NSEWaterSolver(Vector2i(tesslation.x+1, tesslation.y+1), heightScale, heightMap);

			// Create verticies (VertexPCN holds Position, Color, Normal, and texture stage 1)
			GeometryChunk* gc = new GeometryChunk(SHADER_NSE_WATER, hpLength, tesslation.x*tesslation.y*6);
			gc->worldMatrix = worldMatrix;

			s32 i = 0;
			for (s32 y = 0; y < tesslation.y; y++)
			{
				for (s32 x = 0; x < tesslation.x; x++)
				{
					gc->geometry->indicies[i]	= y*(tesslation.x+1) + x;
					gc->geometry->indicies[i+1]	= y*(tesslation.x+1) + x+1;
					gc->geometry->indicies[i+2]	= (y+1)*(tesslation.x+1) + x;
					gc->geometry->indicies[i+3]	= (y+1)*(tesslation.x+1) + x;
					gc->geometry->indicies[i+4]	= y*(tesslation.x+1) + x+1;
					gc->geometry->indicies[i+5]	= (y+1)*(tesslation.x+1) + x+1;
					i += 6;
				}
			}

			// Push back geometry chunk
			chunks.push_back(gc);

			// Transform pickPlane with the localMatrix
			worldMatrix.TransformPlane(pickPlane);
		}

		NSEHeightmapWater::~NSEHeightmapWater()
		{
			delete[] heightMap;
			heightMap = 0;
		}

		void NSEHeightmapWater::Update()
		{
			waterSolver->Simulate();
		}

		void NSEHeightmapWater::Pick(const Linef& ray)
		{
			Vector3f intersect;
			
			if (pickPlane.IntersectsLine(ray.start, ray.GetDirection(), intersect))
			{
				// Calcualte nearest gridpoint and apply force
				// TODO: Must make dynamic, only works if the water plane is where it is now...
				s32 x = (s32) (intersect.x * (tesslation.x/dimension.width));
				s32 z = (s32) (-intersect.z * (tesslation.y/dimension.height));

				if (x > 0 && x < tesslation.x && z > 0 && z < tesslation.y) 
					waterSolver->ApplyForce(x, z, 0.1f);
			}
		
		}

		void NSEHeightmapWater::BuildRenderQueue(const ViewFrustum* frustum, RenderQueue* renderQueue)
		{
			Tesslate();
			ComputeHeightfieldNormals();
			IGeometryNode::BuildRenderQueue(frustum, renderQueue);
		}

		void NSEHeightmapWater::Tesslate()
		{
			f32 xDist = (f32) dimension.width / tesslation.x;
			f32 yDist = (f32) dimension.height / tesslation.y;
			f32 dy = 0; f32 dx = 0;
			s32 xsz = tesslation.x + 1; s32 ysz = tesslation.y + 1;
			f32 tdx = (f32) 1 / tesslation.x; f32 tdy = (f32) 1 / tesslation.y;
			f32 tx = 0; f32 ty = 0;


			for (s32 y = 0; y < ysz; y++, dy += yDist, ty += tdy)
			{
				for (s32 x = 0; x < xsz; x++, dx += xDist, tx += tdx)
				{
					chunks.front()->geometry->verticies[y*xsz + x].position.Set(dx, heightMap[y*xsz + x], -dy);
					chunks.front()->geometry->verticies[y*xsz + x].stage1.Set(tx, ty);
				}

				dx = 0;
				tx = 0;
			}
		}

		void NSEHeightmapWater::ComputeHeightfieldNormals()
		{
			f32 l;
			Vector3f* N;
			s32 xsm = tesslation.x;
			s32 ysm = tesslation.y; 
			s32 xsz = tesslation.x + 1;
			s32 ysz = tesslation.y + 1;

			for(s32 y = 0; y < ysz; y++ )
			{
				for(s32 x = 0; x < xsz; x++ ) 
				{
					// Access current normalmap grid point
					N = &chunks.front()->geometry->verticies[y*xsz + x].normal;

					// Compute normal by using the height differential
					N->x = heightMap[y*xsz + ( !x ? 0 : x-1)] - heightMap[y*xsz + ( x == xsm ? xsm : x+1 )];
					N->y = heightMap[( !y ? 0 : y-1)*xsz + x] - heightMap[( y == ysm ? ysm : y+1 )*xsz + x];
					N->z = (2.0f / (f32)xsz) + (2.0f / (f32)ysz);

					// Normalize it
					l = sqrt(N->x*N->x + N->y*N->y + N->z*N->z); 

					if( l != 0 ) 
					{ 
						N->x /= l; 
						N->y /= l;
						N->z /= l; 
					} 
					else 
						N->x = N->y = N->z = 0.0f;
				}  
			}
		}

	}
}