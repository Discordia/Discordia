#include "Camera.h"

namespace Discordia
{	
	namespace Scene
	{
		Camera::Camera(const Vector3f& e, const Vector3f& a, const Vector3f& upp)
			: ICamera(),
			projNeedUpdate(true), 
			viewNeedUpdate(true),
			eye(e), at(a), up(upp)
		{
			fov		= 45;
			aspect	= 4 / 3;
			zNear	= 0.1f;
			zFar	= 2000;

			at.Normalize();
			right = at^up;
			right.Normalize();
			up = right^at;
			up.Normalize();
		}

		Camera::Camera(const Vector3f& e, const Vector3f& a, const Vector3f& upp, const Dimension2D<s32>& windowDim)
			: ICamera(),
			projNeedUpdate(true), 
			viewNeedUpdate(true),
			eye(e), at(a), up(upp)
		{
			fov		= 45.0f;
			aspect	= (f32) windowDim.width / windowDim.height;
			zNear	= 0.1f;
			zFar	= 2000;

			at.Normalize();
			right = at^up;
			right.Normalize();
			up = right^at;
			up.Normalize();
		}

		Camera::~Camera()
		{
		}

		// Matricies
		void Camera::SetProjectionMatrix(const Matrix4& projMatrix)
		{
			projection = projMatrix;
		}

		const Matrix4& Camera::GetProjectionMatrix()
		{
			if (projNeedUpdate)
				UpdateProjection();

			projNeedUpdate = false;
			return projection;
		}

		bool Camera::HasProjectionChanged()
		{
			return projNeedUpdate;
		}

		const Matrix4& Camera::GetViewMatrix()
		{
			if (viewNeedUpdate)
				UpdateView();

			viewNeedUpdate = false;
			return view;
		}

		bool Camera::HasViewChanged()
		{
			return viewNeedUpdate;
		}

		// Eye, at, up vector
		void Camera::SetEye(const Vector3f& e)
		{
			eye = e;
			viewNeedUpdate = true;
		}

		void Camera::SetAt(const Vector3f& a)
		{
			at = a;
			viewNeedUpdate = true;
		}

		void Camera::SetUp(const Vector3f& upp)
		{
			up = upp;
			viewNeedUpdate = true;
		}

		const Vector3f&	Camera::GetEye()
		{
			return eye;
		}

		const Vector3f&	Camera::GetAt()
		{
			return at;
		}

		const Vector3f&	Camera::GetUp()
		{
			return up;
		}

		// Fustrum
		void Camera::SetNear(const f32& zn)
		{
			zNear = zn;
			projNeedUpdate = true;
		}

		void Camera::SetFar(const f32& zf)
		{
			zFar = zf;
			projNeedUpdate = true;
		}

		void Camera::SetFOV(const f32& field)
		{
			fov = field;
			projNeedUpdate = true;
		}

		void Camera::SetAspectRation(const f32& ratio)
		{
			aspect = ratio;
			projNeedUpdate = true;
		}

		const f32& Camera::GetNear()
		{
			return zNear;
		}

		const f32& Camera::GetFar()
		{
			return zFar;
		}

		const f32& Camera::GetFOV()
		{
			return fov;
		}

		const f32& Camera::GetAspectRatio()
		{
			return aspect;
		}

		ViewFrustum* Camera::GetViewFrustum() 
		{
			return &viewFrustum;
		}

		void Camera::UpdateProjection()
		{
			projection.CreatePerspective(fov, aspect, zNear, zFar);
		}

		void Camera::UpdateFrustum()
		{
			viewFrustum = ViewFrustum(view*projection);
		}

		void Camera::RotateAroundAxis(const f32& angle, const Vector3f& axis)
		{

		}

		void Camera::RotateAroundAt(const f32& angle, const Vector3f& axis)
		{

		}


	}
}