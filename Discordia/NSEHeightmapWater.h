#ifndef NSE_HEIGHT_MAP_WATER_H_INCLUDED
#define NSE_HEIGHT_MAP_WATER_H_INCLUDED

#include "IGeometryNode.h"
#include "NSEWaterSolver.h"
#include "Dimension2D.h"

namespace Discordia
{
	namespace Scene
	{
		/**
		 *  A geometry node that holds a hightmaped surface that can interact with the
		 *  enviorment as it where water. Uses the Physic::NSEWaterSolver to calulate
		 *  heights.
		 */
		class NSEHeightmapWater : public IGeometryNode
		{
		public:
			NSEHeightmapWater(ISceneNode* parent, const Matrix4& localTransform, const Dimension2D<s32>& dim, const f32& hscale, const Vector2i& tesslation);
			virtual ~NSEHeightmapWater();

			void Update();
			void Pick(const Linef& ray);
			void BuildRenderQueue(const ViewFrustum* frustum, RenderQueue* renderQueue);

		protected:
			void Tesslate();
			void ComputeHeightfieldNormals();

		protected:
			Physic::NSEWaterSolver* waterSolver;
			f32*					heightMap;
			const Dimension2D<s32>	dimension;
			const Vector2i			tesslation;
			const f32				heightScale;	
			Planef					pickPlane;
		};
	}
}


#endif