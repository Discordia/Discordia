#include "SceneManager.h"
#include "SceneViewCamera.h"
#include "BoxNode.h"

namespace Discordia
{
	namespace Scene
	{
		SceneManager::SceneManager(IShaderSystem* shaderSystem, IResourceManager* resourceManager, RenderEnviorment* renderEnv)
			: ISceneManager(0, Matrix4()), shaderSystem(shaderSystem), resourceManager(resourceManager), renderEnv(renderEnv)
		{
			camera = new SceneViewCamera(this, renderEnv->GetScreenDim());
		}

		SceneManager::~SceneManager()
		{
		}

		IResourceManager* SceneManager::GetResourceManager()
		{
			return resourceManager;
		}

		RenderEnviorment* SceneManager::GetRenderEnv()
		{
			return renderEnv;
		}

		ISceneNode* SceneManager::GetRoot()
		{
			return this;
		}

		void SceneManager::AddCamera(ICamera* cam)
		{
			camera = cam;
		}

		void SceneManager::AddNSEWaterNode(const Matrix4& localTransform, const Dimension2D<s32>& dim, const f32& hscale, const Vector2i& tesslation)
		{
			NSEHeightmapWater* nseWater = new NSEHeightmapWater(this, localTransform, dim, hscale, tesslation);
			AddChild(nseWater);
		}

		void SceneManager::AddBoxNode(const Matrix4& localTransform, const Vector3f& minCorner, const Vector3f& maxCorner, string textureName)
		{
			weak_ptr<ITexture> tex = resourceManager->GetTexture(textureName);
			shared_ptr<ITexture> shTex = tex.lock();
			BoxNode* box = new BoxNode(this, localTransform, minCorner, maxCorner, shTex);
			AddChild(box);
		}

		void SceneManager::Draw()
		{
			// Set camera
			shaderSystem->SetRenderCamera(camera);

			// GetRenderQueue
			RenderQueue* renderQueue = shaderSystem->GetRenderQueue();

			// Render all children
			BuildRenderQueue(camera->GetViewFrustum(), renderQueue);

			// Render all in render queue
			shaderSystem->DrawRenderQueue();
		}

		void SceneManager::UpdateScene()
		{
			// Call update with identity matrix
			Update(Matrix4());
		}

		bool SceneManager::OnEvent(const Event& event)
		{
			if (camera)
				return camera->OnEvent(event);

			return false;
		}

		Linef SceneManager::GetRayFromScreenCoord(const Vector2i& screenPos, ICamera* camera)
		{
			Linef ray;

			if (!camera)
				camera = this->GetCamera();

			const ViewFrustum* frustum = camera->GetViewFrustum();
			const Dimension2D<s32> screenDim = GetRenderEnv()->GetScreenDim();

			Vector3f farLeftUp = frustum->GetFarLeftUp();
			Vector3f width = frustum->GetFarRightUp() - farLeftUp;
			Vector3f height = frustum->GetFarLeftDown() - farLeftUp;

			f32 dx = screenPos.x / (f32) screenDim.width;
			f32 dy = screenPos.y / (f32) screenDim.height;

			ray.start = camera->GetEye();
			ray.end = farLeftUp + (width * dx) + (height * dy);

			return ray;
		}

	}
}
