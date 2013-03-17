#ifndef ISCENE_MANAGER_H_INCLUDED
#define ISCENE_MANAGER_H_INCLUDED

#include "ISceneNode.h"
#include "IResourceManager.h"
#include "ICamera.h"
#include "Dimension2D.h"

namespace Discordia
{
	namespace Scene
	{
		/**
		 *  Scenemanager interface.
		 */
		class ISceneManager
			: public IEventListener,
			  public ISceneNode
		{
		public:	
			virtual ~ISceneManager() {}

			virtual Graphics::IResourceManager* GetResourceManager() = 0;
			virtual ICamera*					GetCamera() = 0;
			virtual ISceneNode*					GetRoot() = 0;
			virtual Linef						GetRayFromScreenCoord(const Vector2i& screenPos, ICamera* camera) = 0;

			virtual void						AddCamera(ICamera* cam) = 0;
			virtual void						AddNSEWaterNode(const Matrix4& localTransform, const Dimension2D<s32>& dim, const f32& hscale, const Vector2i& tesslation) = 0;
			virtual void						AddBoxNode(const Matrix4& localTransform, const Vector3f& minCorner, const Vector3f& maxCorner, string textureName) = 0;

			virtual void						Draw() = 0;
			virtual void						UpdateScene() = 0;

		protected:
			ISceneManager(ISceneNode* sceneNode, const Matrix4& localTransform) : ISceneNode(0, localTransform) {}
		};
	}
}

#endif