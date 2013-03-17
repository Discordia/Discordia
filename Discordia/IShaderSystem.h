#ifndef ISHADER_SYSTEM_H_INCLUDED
#define ISHADER_SYSTEM_H_INCLUDED

#include "RenderQueue.h"
#include "Matrix4.h"
#include "ICamera.h"

namespace Discordia
{
	namespace Shader
	{
		/**
		 *  Begining of the interface of the sahder system, if I where to continue
		 *  developing this engine this would probobly grow alot. The shader system should be made 
		 *  totally dynamic, today it's very static to get this demo ready sometime.
		 */
		class IShaderSystem
		{
		public:
			virtual ~IShaderSystem() {}

			virtual RenderQueue*	GetRenderQueue() = 0;
			virtual void			SetRenderCamera(Scene::ICamera* camera) = 0;
			virtual void			DrawRenderQueue() = 0;

		protected:
			IShaderSystem() {}
		};
	}
}

#endif