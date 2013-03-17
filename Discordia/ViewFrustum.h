#ifndef VIEW_FRUSTUM_H_INCLUDED
#define VIEW_FRUSTUM_H_INCLUDED

#include "Plane.h"
#include "Matrix4.h"

namespace Discordia
{
	namespace Scene
	{
		enum FrustumPlane
		{
			PLANE_LEFT = 0,
			PLANE_RIGHT,
			PLANE_TOP,
			PLANE_BOTTOM,
			PLANE_NEAR,
			PLANE_FAR,
			PLANE_COUNT
		};

		/** 
		 *	Class that holds the viewfrustum planes.
		 */
		class ViewFrustum
		{
		public:
			ViewFrustum() {}		
			ViewFrustum(const Matrix4& m);
			~ViewFrustum() {}

			// Corner positions of the view frustum
			Vector3f GetFarRightDown() const;
			Vector3f GetFarLeftDown() const;
			Vector3f GetFarLeftUp() const;
			Vector3f GetFarRightUp() const;

			void Transform(const Matrix4& matrix);

		public:
			Planef		frustumPlanes[PLANE_COUNT];
		};

		inline ViewFrustum::ViewFrustum(const Matrix4& m)
		{

			// Right
			frustumPlanes[PLANE_RIGHT].normal.x = m.matrix[3] - m.matrix[0];
			frustumPlanes[PLANE_RIGHT].normal.y = m.matrix[7] - m.matrix[4];
			frustumPlanes[PLANE_RIGHT].normal.z = m.matrix[11] - m.matrix[8];
			frustumPlanes[PLANE_RIGHT].D = m.matrix[15] - m.matrix[12];

			// Left
			frustumPlanes[PLANE_LEFT].normal.x = m.matrix[3] + m.matrix[0];
			frustumPlanes[PLANE_LEFT].normal.y = m.matrix[7] + m.matrix[4];
			frustumPlanes[PLANE_LEFT].normal.z = m.matrix[11] + m.matrix[8];
			frustumPlanes[PLANE_LEFT].D = m.matrix[15] + m.matrix[12];

			// Bottom
			frustumPlanes[PLANE_BOTTOM].normal.x = m.matrix[3] + m.matrix[1];
			frustumPlanes[PLANE_BOTTOM].normal.y = m.matrix[7] + m.matrix[5];
			frustumPlanes[PLANE_BOTTOM].normal.z = m.matrix[11] + m.matrix[9];
			frustumPlanes[PLANE_BOTTOM].D = m.matrix[15] + m.matrix[13];

			// Top
			frustumPlanes[PLANE_TOP].normal.x = m.matrix[3] - m.matrix[1];
			frustumPlanes[PLANE_TOP].normal.y = m.matrix[7] - m.matrix[5];
			frustumPlanes[PLANE_TOP].normal.z = m.matrix[11] - m.matrix[9];
			frustumPlanes[PLANE_TOP].D = m.matrix[15] - m.matrix[13];

			// Far
			frustumPlanes[PLANE_FAR].normal.x = m.matrix[3] - m.matrix[2];
			frustumPlanes[PLANE_FAR].normal.y = m.matrix[7] - m.matrix[6];
			frustumPlanes[PLANE_FAR].normal.z = m.matrix[11] - m.matrix[10];
			frustumPlanes[PLANE_FAR].D = m.matrix[15] - m.matrix[14];

			// Near
			frustumPlanes[PLANE_NEAR].normal.x = m.matrix[3] + m.matrix[2];
			frustumPlanes[PLANE_NEAR].normal.y = m.matrix[7] + m.matrix[6];
			frustumPlanes[PLANE_NEAR].normal.z = m.matrix[11] + m.matrix[10];
			frustumPlanes[PLANE_NEAR].D = m.matrix[15] + m.matrix[14];

			// Normalise planes
			for (s32 i = 0; i < PLANE_COUNT; ++i)
			{
				f32 length = (f32)(1.0f / frustumPlanes[i].normal.Abs());
				frustumPlanes[i].normal *= length;
				frustumPlanes[i].D *= length;
			}
		}

		inline Vector3f ViewFrustum::GetFarRightDown() const
		{
			Vector3f interPos;

			frustumPlanes[PLANE_FAR].IntersectsPlanes(frustumPlanes[PLANE_BOTTOM], 
													  frustumPlanes[PLANE_RIGHT], 
													  interPos);

			return interPos;
		}

		inline Vector3f ViewFrustum::GetFarLeftDown() const
		{
			Vector3f interPos;
	
			frustumPlanes[PLANE_FAR].IntersectsPlanes(frustumPlanes[PLANE_BOTTOM], 
													  frustumPlanes[PLANE_LEFT], 
													  interPos);

			return interPos;
		}

		inline Vector3f ViewFrustum::GetFarLeftUp() const
		{
			Vector3f interPos;

			frustumPlanes[PLANE_FAR].IntersectsPlanes(frustumPlanes[PLANE_TOP], 
													  frustumPlanes[PLANE_LEFT], 
													  interPos);

			return interPos;
		}

		inline Vector3f ViewFrustum::GetFarRightUp() const
		{
			Vector3f interPos;

			frustumPlanes[PLANE_FAR].IntersectsPlanes(frustumPlanes[PLANE_TOP], 
													  frustumPlanes[PLANE_RIGHT], 
													  interPos);

			return interPos;
		}

		inline void ViewFrustum::Transform(const Matrix4& matrix)
		{
			for (s32 i = 0; i < PLANE_COUNT; i++)
				matrix.TransformPlane(frustumPlanes[i]);
		}
	}
}


#endif