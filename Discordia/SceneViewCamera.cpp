#include "SceneViewCamera.h"
#include "Picking.h"

namespace Discordia
{
	namespace Scene
	{
		SceneViewCamera::SceneViewCamera(ISceneManager* sceneManager)
			: Camera(Vector3f(0, 10, 30), Vector3f(0, 0, -1), Vector3f(0, 1, 0)), sceneManager(sceneManager), altDown(false)
		{
			for (int i = 0; i < 3; i++)
				mouseButton[i] = false;

			UpdateFrustum();
		}

		SceneViewCamera::SceneViewCamera(ISceneManager* sceneManager, const Dimension2D<s32>& windowDim)
			: Camera(Vector3f(10, 40, 25), Vector3f(0, 0, -1), Vector3f(0, 1, 0), windowDim), sceneManager(sceneManager), altDown(false)
		{
			for (int i = 0; i < 3; i++)
				mouseButton[i] = false;

			Matrix4 rotMatrix;
			rotMatrix.SetRotationDegree(-50, right);
			rotMatrix.TransformVector(at);
			rotMatrix.TransformVector(up);
			right = at^up;
			right.Normalize();

			view.CreateLookAt(eye, at, up);
			UpdateFrustum();
		}

		SceneViewCamera::SceneViewCamera(ISceneManager* sceneManager, const Vector3f& eye, const Vector3f& at)
			: Camera(eye, at, Vector3f(0, 1, 0)), sceneManager(sceneManager), altDown(false)
		{
			for (int i = 0; i < 3; i++)
				mouseButton[i] = false;

			UpdateFrustum();
		}

		SceneViewCamera::SceneViewCamera(ISceneManager* sceneManager, const Vector3f& eye, const Vector3f& at, const Vector3f& up)
			: Camera(eye, at, up), sceneManager(sceneManager), altDown(false)
		{
			for (int i = 0; i < 3; i++)
				mouseButton[i] = false;

			UpdateFrustum();
		}

		SceneViewCamera::~SceneViewCamera()
		{
		}

		bool SceneViewCamera::OnEvent(const Event& event)
		{
			switch(event.eventType) 
			{
			case ET_KEY_EVENT:
				switch(event.KeyEvent.keyCode)
				{
				case KEY_LALT:
					altDown = event.KeyEvent.isDown;
					lastMousePos = newMousePos;
					break;

				default: 
					return false;
				}

			case ET_MOUSE_EVENT:
				switch(event.MouseEvent.event)
				{
				case MIE_LEFT_MOUSE_BUTTON_DOWN:
					mouseButton[0] = true;
					lastMousePos = newMousePos;
					break;

				case MIE_MIDDLE_MOUSE_BUTTON_DOWN:
					mouseButton[1] = true;
					lastMousePos = newMousePos;
					break;

				case MIE_RIGHT_MOUSE_BUTTON_DOWN:
					mouseButton[2] = true;
					lastMousePos = newMousePos;
					break;

				case MIE_LEFT_MOUSE_BUTTON_UP:
					mouseButton[0] = false;
					break;
						
				case MIE_MIDDLE_MOUSE_BUTTON_UP:
					mouseButton[1] = false;
					break;

				case MIE_RIGHT_MOUSE_BUTTON_UP:
					mouseButton[2] = false;
					break;

				case MIE_MOUSE_MOVED:
					lastMousePos = newMousePos;
					newMousePos = Vector2i(event.MouseEvent.x, event.MouseEvent.y);
					break;

				default:
					return false;
				}
				break;

			default:
				return false;
			}

			viewNeedUpdate = true;
			return true;
		}

		void SceneViewCamera::UpdateView()
		{
			if (altDown)
			{
				if (mouseButton[0]) // Rotate X and Y
				{
					s32 xDiff = newMousePos.x - lastMousePos.x;
					s32 yDiff = newMousePos.y - lastMousePos.y;
					Matrix4 rotMatrix;

					if (yDiff != 0)
					{
						rotMatrix.SetRotationDegree(-(f32) yDiff/3.0f, right);
						rotMatrix.TransformVector(at);
						rotMatrix.TransformVector(up);
						right = at^up;
						right.Normalize();
					}

					if (xDiff != 0)
					{
						rotMatrix.SetRotationDegree(-(f32) xDiff /3.0f, up);
						rotMatrix.TransformVector(at);
						rotMatrix.TransformVector(up);
						right = at^up;
						right.Normalize();
					}
				}
				else if (mouseButton[1]) // Translate X and Z
				{
					
				}
				else if (mouseButton[2]) // Zoom (Translate along the view vector)
				{
					s32 xDiff = newMousePos.x - lastMousePos.x;
					s32 yDiff = newMousePos.y - lastMousePos.y;

					if (yDiff != 0)
						eye += at*(f32)yDiff/4.0f;
					
					if (xDiff != 0)
						eye += right*(f32)xDiff/4.0f;

				}
			}
			else if (mouseButton[0]) // Pick nodes
			{
				// Get ray from screen coordinates
				Linef ray = sceneManager->GetRayFromScreenCoord(newMousePos, this);

				// Travers scenegraph and pick the right node
				sceneManager->PickNode(ray);
			}

			view.CreateLookAt(eye, at, up);
			UpdateFrustum();
		}

	}
}