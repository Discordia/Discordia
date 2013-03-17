#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "ICamera.h"
#include "Quaternion.h"
#include "Dimension2D.h"

namespace Discordia
{
	namespace Scene
	{
		/**
		 *  Camera, holds projection and calculates/updates view matrix.
		 */
		class Camera : public ICamera
		{
		public:
			virtual ~Camera();

			// Matricies
			void				SetProjectionMatrix(const Matrix4& projMatrix);
			const Matrix4&		GetProjectionMatrix();
			bool				HasProjectionChanged();
			const Matrix4&		GetViewMatrix();
			bool				HasViewChanged();

			// Eye, at, up vector
			void				SetEye(const Vector3f& eye);
			void				SetAt(const Vector3f& at);
			void				SetUp(const Vector3f& up);
			const Vector3f&		GetEye();
			const Vector3f&		GetAt();
			const Vector3f&		GetUp();

			// Fustrum
			void				SetNear(const f32& zNear);
			void				SetFar(const f32& zFar);
			void				SetFOV(const f32& fov);
			void				SetAspectRation(const f32& aspect);
			const f32&			GetNear();
			const f32&			GetFar();
			const f32&			GetFOV();
			const f32&			GetAspectRatio();
			ViewFrustum*		GetViewFrustum();

		protected:
			Camera(const Vector3f& eye, const Vector3f& at, const Vector3f& up);							
			Camera(const Vector3f& eye, const Vector3f& at, const Vector3f& up, const Dimension2D<s32>& windowDim);

			virtual void	UpdateView() {}
			void			UpdateProjection();
			void			UpdateFrustum();

			// Transformas
			void RotateAroundAxis(const f32& angel, const Vector3f& axis);
			void RotateAroundAt(const f32& angel, const Vector3f& axis);

		protected:
			// Matrix
			Matrix4			projection;
			Matrix4			view;

			// Camera vectors
			Vector3f		eye;
			Vector3f		at;
			Vector3f		up;
			Vector3f		right;

			// Fustrum values
			f32				fov;
			f32				aspect;
			f32				zNear;
			f32				zFar;
			ViewFrustum	viewFrustum;

			// Updating
			bool			viewNeedUpdate;
			bool			projNeedUpdate;
		};
	}
}


#endif