#ifndef VECTOR2_H_INCLUDED
#define VECTOR2_H_INCLUDED

#include "Types.h"
#include <math.h>

namespace Discordia
{
	template<class T>
	class Vector2 
	{
	public:
		Vector2()
			: x(0), y(0) {};

		Vector2(T xx, T yy)
			: x(xx), y(yy) {};

		Vector2(const Vector2<T>& v)
			: x(v.x), y(v.y) {};

		~Vector2() {}

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
		Vector2<T>& operator=(const Vector2<T> &v)
		{
			x = v.x;
			y = v.y;

			return *this;
		}

		/* Methods for setting the elements */
		void Set(T xx, T yy)
		{
			x = xx;
			y = yy;
		}

		void Set(Vector2<T> v)
		{
			x = v.x;
			y = v.y;
		}

		/* Relation operators */
		bool operator ==(const Vector2<T> &p) const 
		{
			return ((x == p.x) && (y == p.y));
		}
		bool operator !=(const Vector2<T> &p) const 
		{
			return !((*this) == p);
		}

		/* Simple arithmetics */
		Vector2<T>& operator+=(const Vector2<T> &p) 
		{
			x += p.x;
			y += p.y;

			return *this;
		}

		Vector2<T> operator+(const Vector2<T> &p) const 
		{
			return Vector2<T>(x + p.x, y + p.y);
		}

		Vector2<T>& operator-=(const Vector2<T> &p) 
		{
			x -= p.x; 
			y -= p.y;

			return *this;
		}

		Vector2<T> operator-(const Vector2<T> &p) const 
		{
			return Vector2<T>(x - p.x, y - p.y);
		}

		Vector2<T> operator-() const 
		{
			return Vector2<T>(-x, -y);
		}

		Vector2<T>& operator*=(const T s) 
		{
			x *= s;
			y *= s;

			return *this;
		}

		Vector2<T> operator*(const T o) const 
		{
			return Vector2<T>(x*o, y*o);
		}

		Vector2<T>& operator/=(T o) 
		{
			x /= o;
			y /= o;

			return *this;
		}

		Vector2<T> operator/(T o) const 
		{
			return Vector2<T>(x/o, y/o);
		}

		/* Scalar product */
		T  operator*(const Vector2<T> &v) const 
		{
			return x*v.x + y*v.y;
		}

		/* Vector product */
		Vector2<T> operator^(const Vector2<T> &v) const 
		{
			Vector2<T> tmp;
			tmp.x = y*v.z - z*v.y;
			tmp.y = z*v.x - x*v.z;

			return tmp;
		}

		/* Absolut value */
		f32 Abs() const 
		{
			return sqrtf((*this)*(*this));
		}

		/* Normalize */
		Vector2<T> &Normalize() 
		{
			return (*this) /= (T) Abs();
		}

	public:
		T x, y;
	};

	typedef Vector2<s32> Vector2i;
	typedef Vector2<f32> Vector2f;
}

#endif