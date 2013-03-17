#ifndef VECTOR3_H_INCLUDED
#define VECTOR3_H_INCLUDED

#include "Vector2.h"

namespace Discordia
{
	template<class T>
	class Vector3
	{
	public:
		Vector3()
			: x(0), y(0), z(0) {};

		Vector3(T xx, T yy, T zz)
			: x(xx), y(yy), z(zz) {};

		Vector3(const Vector3<T>& v)
			: x(v.x), y(v.y), z(v.z) {};

		~Vector3() {}

		/* []-operator to get elements */
		// Will cause an error if i is out of range
		T& operator[](s32 i) 
		{
			return (&x)[i];
		}

		const T& operator[](s32 i) const 
		{
			return (&x)[i];
		}

		/* Assigment operator */
		Vector3<T>& operator=(const Vector3<T> &v)
		{
			x = v.x;
			y = v.y;
			z = v.z;

			return *this;
		}

		/* Methods for setting the elements */
		void Set(T xx, T yy, T zz)
		{
			x = xx;
			y = yy;
			z = zz;
		}

		void Set(Vector3<T> v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
		}

		/* Relation operators */
		bool operator ==(const Vector3<T> &p) const 
		{
			return ((x == p.x) && (y == p.y) && (z == p.z));
		}
		bool operator !=(const Vector3<T> &p) const 
		{
			return !((*this) == p);
		}

		/* Simple arithmetics */
		Vector3<T>& operator+=(const Vector3<T> &p) 
		{
			x += p.x;
			y += p.y;
			z += p.z;

			return *this;
		}

		Vector3<T> operator+(const Vector3<T> &p) const 
		{
			return Vector3<T>(x + p.x, y + p.y, z + p.z);
		}

		Vector3<T>& operator-=(const Vector3<T> &p) 
		{
			x -= p.x; 
			y -= p.y;
			z -= p.z;

			return *this;
		}

		Vector3<T> operator-(const Vector3<T> &p) const 
		{
			return Vector3<T>(x - p.x, y - p.y, z - p.z);
		}

		Vector3<T> operator-() const 
		{
			return Vector3<T>(-x, -y, -z);
		}

		Vector3<T>& operator*=(const T s) 
		{
			x *= s;
			y *= s;
			z *= s;

			return *this;
		}

		Vector3<T> operator*(const T o) const 
		{
			return Vector3<T>(x*o, y*o, z*o);
		}

		Vector3<T>& operator/=(T o) 
		{
			x /= o;
			y /= o;
			z /= o;

			return *this;
		}

		Vector3<T> operator/(T o) const 
		{
			return Vector3<T>(x/o, y/o, z/o);
		}

		/* Scalar product */
		T  operator*(const Vector3<T> &v) const 
		{
			return x*v.x + y*v.y + z*v.z;
		}

		/* Vector product */
		Vector3<T> operator^(const Vector3<T> &v) const 
		{
			Vector3<T> tmp;
			tmp.x = y*v.z - z*v.y;
			tmp.y = z*v.x - x*v.z;
			tmp.z = x*v.y - y*v.x;

			return tmp;
		}

		/* Absolut value */
		f32 Abs() const 
		{
			return sqrtf((*this)*(*this));
		}

		/* Normalize */
		Vector3<T> &Normalize() 
		{
			return (*this) /= (T) Abs();
		}

		/* Euclidian distance */
		f32 DistanceTo(const Vector3& point) const
		{
			f32 xx = x - point.x;
			f32 yy = y - point.y;
			f32 zz = z - point.z;
			return sqrtf(xx*xx + yy*yy ++ zz*zz);
		}

	public:
		T x, y, z;
	};

	typedef Vector3<s32> Vector3i;
	typedef Vector3<f32> Vector3f;
}

#endif