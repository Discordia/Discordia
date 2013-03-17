#ifndef MATRIX4_H_INCLUDED
#define MATRIX4_H_INCLUDED

#include <string.h>
#include "Plane.h"

namespace Discordia
{
	class Matrix4 
	{
	public:
		Matrix4() { Identity(); };
		Matrix4(const f32 m[16]) { Set(m); };
		Matrix4(const Matrix4& m) { Set(m.matrix	); };
		
		void Clear() { memset(matrix, 0, sizeof(f32)*16); };
		Matrix4& Identity() 
		{
			Clear(); 
			matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1;
			return *this;
		}

		void Set(const f32 m[16])
		{
			memcpy(matrix, m, 16*sizeof(f32));
		}

		/* ()-operator to get elements */
		f32& operator()(s32 col, s32 row) 
		{
			return matrix[row*4 + col];	
		}

		const f32& operator()(s32 row, s32 col) const 
		{
			return matrix[row*4 + col];	
		}

		/* Multiplication */
		Matrix4 operator*(const Matrix4& m) const;
		Matrix4& operator*=(const Matrix4& m) { return (*this) = (*this)*m; };
		Matrix4 operator*(const f32& f) const;
		Matrix4& operator*=(const f32& f) { return (*this) = (*this)*f; };

		/* Typomvandligsoperator */
		operator f32*()
		{
			return matrix;
		}

		/* Transpose */
		Matrix4 Transpose() const;

		// Determinant, not implemented 
		// TODO: Not implementred
		f32 Determinant() const {} 

		// Inverse 
		// TODO: Not implemented
		Matrix4 Inverse() const;


		// Aditional computer graphics oriented methods
		void CreatePerspective(f32 fov, f32 aspectRatio, f32 zNear, f32 zFar);
		void CreatePerspective(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);
		void CreateLookAt(Vector3f eye, Vector3f at, Vector3f up);
		void SetTranslation(const Vector3f& transVect);
		void SetScale(const Vector3f& scaleVect);
		void SetRotationDegree(const f32& angle, Vector3f& rotVect);
		void SetRotationRadian(const f32& angle, Vector3f& rotVect);
		void TransformVector(Vector3f& v) const;
		void TransformPlane(Planef& plane) const;
		void TransformPoint(Vector3f& p) const;

	public:
		f32 matrix[16];
	};

	inline Matrix4 Matrix4::operator*(const Matrix4& m) const
	{
		Matrix4 tmp;

		for (s32 i = 0; i < 4; i++)
		{
			for (s32 j = 0; j < 4; j++)
			{
				tmp.matrix[i*4 + j] = 0.0f;

				for (s32 k = 0; k < 4; k++)
					tmp.matrix[i*4 + j] += matrix[i*4 + k]*m.matrix[k*4 + j];		
			}
		}

		return tmp;
	}

	inline Matrix4 Matrix4::operator*(const f32& f) const
	{
		Matrix4 tmp;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				tmp.matrix[i*4 + j] = matrix[i*4 + j]*f;
		}

		return tmp;
	}

	inline Matrix4 Matrix4::Transpose() const 
	{
		Matrix4 tmp;

		for (int i = 0; i < 4; i++) 
		{
			for(int j = 0; j < 4; j++) 
				tmp.matrix[i*4 + j] = matrix[j*4 + i];       
		}

		return tmp;
	}


	inline void Matrix4::CreatePerspective(f32 fov, f32 aspectRatio, f32 zNear, f32 zFar)
	{
		f32 fovRadian = Utility::DegreeToRadianf(fov);
		f32 h = (f32)(cos(fovRadian/2) / sin(fovRadian/2));
		f32 w = h / aspectRatio;
		f32 C = -((zFar + zNear) / (zFar - zNear));
		f32 D = -2*((zFar*zNear) / (zFar - zNear));

		matrix[0]	= w/(zNear*2);
		matrix[1]	= 0.0f;
		matrix[2]	= 0.0f;
		matrix[3]	= 0.0f;

		matrix[4]	= 0.0f;
		matrix[5]	= h/(zNear*2);
		matrix[6]   = 0.0f;
		matrix[7]	= 0.0f;

		matrix[8]	= 0.0f;
		matrix[9]   = 0.0f;
		matrix[10]  = C;
		matrix[11]  = -1.0f;

		matrix[12]	= 0.0f;
		matrix[13]	= 0.0f;
		matrix[14]	= D;
		matrix[15]	= 0.0f;
	}

	inline void Matrix4::CreatePerspective(f32 left, f32 right, f32 bottom, f32 top, f32 zNear, f32 zFar)
	{
		f32 C = -((zFar + zNear) / (zFar - zNear));
		f32 D = -2*((zFar*zNear) / (zFar - zNear));

		matrix[0]	= 2*zNear / (right - left);
		matrix[1]	= 0.0f;
		matrix[2]	= 0.0f;
		matrix[3]	= 0.0f;
	
		matrix[4]	= 0.0f;
		matrix[5]	= 2*zNear / (top - bottom);
		matrix[6]	= 0.0f;
		matrix[7]	= 0.0f;

		matrix[8]	= 0.0f;
		matrix[9]	= 0.0f;
		matrix[10]	= C;
		matrix[11]	= -1.0f;

		matrix[12]	= 0.0f;
		matrix[13]	= 0.0f;
		matrix[14]	= D;
		matrix[15]	= 0.0f;
	}

	inline void Matrix4::CreateLookAt(Vector3f eye, Vector3f at, Vector3f up)
	{
		at.Normalize();
		Vector3f right = at^up;
		right.Normalize();
		up = right^at;
		up.Normalize();

		matrix[0] =  right.x;
		matrix[1] =  up.x;
		matrix[2] = -at.x;
		matrix[3] =  0.0f;

		matrix[4] =  right.y;
		matrix[5] =  up.y;
		matrix[6] = -at.y;
		matrix[7] =  0.0f;

		matrix[8]  =  right.z;
		matrix[9]  =  up.z;
		matrix[10] = -at.z;
		matrix[11] =  0.0f;

		matrix[12] = -right*eye;
		matrix[13] = -up*eye;;
		matrix[14] =  at*eye;
		matrix[15] =  1.0f;
	}

	inline void Matrix4::SetTranslation(const Vector3f& transVect)
	{
		matrix[12]	= transVect.x;
		matrix[13]	= transVect.y;
		matrix[14]	= transVect.z;
	}

	inline void Matrix4::SetScale(const Vector3f& scaleVect)
	{
		matrix[0]	= scaleVect.x;
		matrix[5]	= scaleVect.y;
		matrix[10]	= scaleVect.z;
	}
	
	inline void Matrix4::SetRotationDegree(const f32& angle, Vector3f& rotVect)
	{
		SetRotationRadian(angle*(f32)DEG_TO_RAD, rotVect);
	}

	inline void Matrix4::SetRotationRadian(const f32& angle, Vector3f& rotVect)
	{
		f32 c = cosf(angle);
		f32 s = sinf(angle);

		rotVect.Normalize();

		f32 ux = rotVect.x;
		f32 uy = rotVect.y;
		f32 uz = rotVect.z;

		matrix[0]  = c + (1-c) * ux;
		matrix[1]  = (1-c) * ux*uy + s*uz;
		matrix[2]  = (1-c) * ux*uz - s*uy;
		matrix[3]  = 0;

		matrix[4]  = (1-c) * uy*ux - s*uz;
		matrix[5]  = c + (1-c) * pow(uy,2);
		matrix[6]  = (1-c) * uy*uz + s*ux;
		matrix[7]  = 0;

		matrix[8]  = (1-c) * uz*ux + s*uy;
		matrix[9]  = (1-c) * uz*uz - s*ux;
		matrix[10] = c + (1-c) * pow(uz,2);
		matrix[11] = 0;

		matrix[12] = 0;
		matrix[13] = 0;
		matrix[14] = 0;
		matrix[15] = 1;
	}

	inline void Matrix4::TransformVector(Vector3f& v) const
	{
		v.Set(v.x*matrix[0] + v.y*matrix[4] + v.z*matrix[8],
			v.x*matrix[1] + v.y*matrix[5] + v.z*matrix[9],
			v.x*matrix[2] + v.y*matrix[6] + v.z*matrix[10]);
	}

	inline void Matrix4::TransformPlane(Planef& p) const
	{
		Vector3f point(p.GetPoint());
		Vector3f origin;

		TransformVector(point);
		TransformVector(p.normal);
		TransformVector(origin);
		
		p.normal -= origin;
		p.D = -point*p.normal;
	}

	inline void Matrix4::TransformPoint(Vector3f& p) const
	{
		p.Set(p.x*matrix[0] + p.y*matrix[4] + p.z*matrix[8]  + matrix[12],
			p.x*matrix[1] + p.y*matrix[5] + p.z*matrix[9]	 + matrix[13],
			p.x*matrix[2] + p.y*matrix[6] + p.z*matrix[10] + matrix[14]);
	}

}

#endif