#ifndef QUATERNION_H_INCLUDED
#define QUATERNION_H_INCLUDED

#include "Vector3.h"

namespace Discordia
{
	template<class T>
	class Quaternion
	{
	public:
		Quaternion()
		{
			v.Set(0.0f, 0.0f, 0.0f);
			w = 0.0f;
		}

		Quaternion(const Vector3<T>& v, const T& w) 
		{
			this->v = v;
			this->w = w;
		}

		Quaternion(const Quaternion<T>& q)
		{
			v = q.v;
			w = q.w;
		}

		~Quaternion() {};

		f32 Length() 
		{
			return sqrtf(v*v + w*w);
		}

		Quaternion<T> Normalize() 
		{
			f32 len = Length();

			this->v /= len;
			this->w /= len;

			return *this;
		}

		Quaternion<T> Conjugate() const
		{
			Quaternion<T> q(-v, w);
			return q;
		}

		Quaternion<T> operator*(const Quaternion<T>& q) const 
		{
			Quaternion<T> quat;
			quat.v.x = this->w*q.v.x + this->v.x*q.w   + this->v.y*q.v.z   - this->v.z*q.v.y;
			quat.v.y = this->w*q.v.y - this->v.x*q.v.z + this->v.y*q.w   + this->v.z*q.v.x;
			quat.v.z = this->w*q.v.z + this->v.x*q.v.y - this->v.y*q.v.x + this->v.z*q.w;

			return quat;
		}

		Quaternion<T>& operator*=(const Quaternion<T>& q)
		{
			v *= q.v;
			w *= w;

			return *this;
		}

	public:
		Vector3<T>		v;
		T				w;
	};

	typedef Quaternion<f32> Quaternionf;
	typedef Quaternion<s32> Quaternioni;
}

#endif