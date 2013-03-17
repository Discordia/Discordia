#ifndef ICAMERA_H_INCLUDED
#define ICAMERA_H_INCLUDED

#include "IEventListener.h"
#include "Matrix4.h"
#include "ViewFrustum.h"

namespace Discordia
{
	namespace Scene
	{
		/** 
		 *	Camera interface.
		 */
		class ICamera : public IEventListener
		{
		public:
			virtual ~ICamera() {}

			// Matricies
			virtual void				SetProjectionMatrix(const Matrix4& projMatrix) = 0;
			virtual const Matrix4&		GetProjectionMatrix() = 0;
			virtual	bool				HasProjectionChanged() = 0;
			virtual const Matrix4&		GetViewMatrix() = 0;
			virtual bool				HasViewChanged() = 0;

			// Eye, at, up vector
			virtual void				SetEye(const Vector3f& eye) = 0;
			virtual void				SetAt(const Vector3f& at) = 0;
			virtual void				SetUp(const Vector3f& up) = 0;
			virtual const Vector3f&		GetEye() = 0;
			virtual const Vector3f&		GetAt() = 0;
			virtual const Vector3f&		GetUp() = 0;

			// Fustrum
			virtual void				SetNear(const f32& zNear) = 0;
			virtual void				SetFar(const f32& zFar) = 0;
			virtual void				SetFOV(const f32& fov) = 0;
			virtual void				SetAspectRation(const f32& aspect) = 0;
			virtual const f32&			GetNear() = 0;
			virtual const f32&			GetFar() = 0;
			virtual const f32&			GetFOV() = 0;
			virtual const f32&			GetAspectRatio() = 0;
			virtual ViewFrustum*		GetViewFrustum() = 0;

		protected:
			ICamera() {}
		};
	}
}


#endif
