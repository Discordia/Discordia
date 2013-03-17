#ifndef SCENE_MANAGER_H_INCLUDED
#define SCENE_MANAGER_H_INCLUDED

#include "ISceneManager.h"
#include "IResourceManager.h"
#include "IShaderSystem.h"
#include "NSEHeightmapWater.h"
#include "RenderEnviorment.h"

using Discordia::Graphics::RenderEnviorment;
using Discordia::Graphics::IResourceManager;
using Discordia::Shader::IShaderSystem;

namespace Discordia
{
	namespace Scene
	{
		/** 
		 *	Scenemanager.
		 */
		class SceneManager : 
			public ISceneManager
		{
		public:
			SceneManager(IShaderSystem* shaderSystem, IResourceManager* resourceManager, RenderEnviorment* renderEnv);
			virtual ~SceneManager();

			IResourceManager*				GetResourceManager();
			RenderEnviorment*				GetRenderEnv();
			ICamera*						GetCamera() {return camera; }
			ISceneNode*						GetRoot();
			Linef							GetRayFromScreenCoord(const Vector2i& screenPos, ICamera* camera);

			void							AddCamera(ICamera* cam);	
			void							AddNSEWaterNode(const Matrix4& localTransform, const Dimension2D<s32>& dim, const f32& hscale, const Vector2i& tesslation);
			void							AddBoxNode(const Matrix4& localTransform, const Vector3f& minCorner, const Vector3f& maxCorner, string textureName);
		
			void							Draw();
			void							UpdateScene();
			bool							OnEvent(const Event& event);
			

		protected:
			Shader::IShaderSystem*			shaderSystem;
			Graphics::IResourceManager*		resourceManager;
			ICamera*						camera;	
			RenderEnviorment*				renderEnv;
		};
	}
}

#endif