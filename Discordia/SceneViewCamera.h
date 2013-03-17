#ifndef SCENE_VIEW_CAMERA_H_INCLUDED
#define SCENE_VIEW_CAMERA_H_INCLUDED

#include "Camera.h"
#include "ISceneManager.h"

namespace Discordia
{
	namespace Scene
	{
		/**
		 *  A camera that can rotate round view direction and Up, 
		 *  and translate in X and view direction. It can also pcik scenenodes and interakt with them.
		 */
		class SceneViewCamera : public Camera
		{
		public:
			SceneViewCamera(ISceneManager* sceneManager);
			SceneViewCamera(ISceneManager* sceneManager, const Dimension2D<s32>& windowDim);
			SceneViewCamera(ISceneManager* sceneManager, const Vector3f& eye, const Vector3f& at);
			SceneViewCamera(ISceneManager* sceneManager, const Vector3f& eye, const Vector3f& at, const Vector3f& up);
			virtual ~SceneViewCamera();

			bool OnEvent(const Event& event);

		protected:
			void UpdateView();

		protected:
			bool			altDown;
			bool			mouseButton[3];
			Vector2i		lastMousePos;
			Vector2i		newMousePos;
			ISceneManager*	sceneManager;
		};
	}
}

#endif