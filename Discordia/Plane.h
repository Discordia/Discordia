#ifndef PLANE_H_INCLUDED
#define PLANE_H_INCLUDED

#include "Vector3.h"
#include "Utility.h"

namespace Discordia
{
	template<class T>
	class Plane
	{
	public:
		Plane() 
			: normal(0, 1, 0)
		{
			CalculateD(Vector3<T>(0, 0, 0));
		}

		Plane(const Vector3<T>& normal, const Vector3<T>& memPoint)
			: normal(normal)
		{
			normal.Normalize();
			CalculateD(memPoint);
		}

		Plane(const Vector3<T>& p1, const Vector3<T>& p2, const Vector3<T>& p3)
		{
			Set(p1, p2, p3);
		}

		Plane(const Plane<T>& plane)
			: normal(plane.normal), D(plane.D)
		{
		}

		void Set(const Vector3<T>& normal, const T& D)
		{
			this->normal = normal;
			this->D = D;
		}

		void Set(const Vector3<T>& normal, const Vector3<T>& memPoint)
		{
			this->normal = normal;
			this->normal.Normalize();
			CalculateD(memPoint);
		}

		void Set(const Vector3<T>& p1, const Vector3<T>& p2, const Vector3<T>& p3)
		{
			normal = (p2 - p1)^(p3 - p1);	
			normal.Normalize();
			CalculateD(p1);
		}

		void CalculateD(const Vector3<T>& memPoint)
		{
			D = - memPoint*normal;
		}

		bool IsFrontFacing(const Vector3<T>& at) const 
		{
			return normal*at <= 0.0f;
		}
		const Vector3<T> GetPoint() const
		{
			return normal * -D;
		}

		bool IntersectsLine(const Vector3<T>& pos, 
							const Vector3<T>& direction, 
							Vector3<T>& intersection) const
		{
			T tmp = normal*direction;

			if (tmp == 0)
				return false;

			T tmp2 = -(normal*pos + D) / tmp;
			intersection = pos + (direction*tmp2);
			return true;
		}

		bool IntersectsPlane(const Plane<T>& p,
							 Vector3<T>& interPos, 
							 Vector3<T>& interDir) const 
		{
			f32 tmp		= normal.Abs();
			f32 tmp2	= normal*p.normal;
			f32 tmp3	= p.normal.Abs();
			f32 tmp4	= tmp*tmp3 - tmp2*tmp2;

			if (fabs(tmp4) < EPSILON)
				return false;

			tmp4 = 1.0f / tmp4;
			f32 tmp5 = (tmp3	* -D   + tmp2 * p.D) * tmp4;
			f32 tmp6 = (tmp	* -p.D + tmp2 * D)	 * tmp4;

			interDir = normal^p.normal;
			interPos = normal*tmp5 + p.normal*tmp6;
			return true;
		}

		bool IntersectsPlanes(const Plane<T>& p1, 
							  const Plane<T>& p2, 
							  Vector3<T>& interPos) const
		{
			Vector3<T> pos, dir;

			if (IntersectsPlane(p1, pos, dir))
				return p2.IntersectsLine(pos, dir, interPos);

			return false;
		}
			

	public:
		Vector3<T>	normal;
		T			D;
	};

	typedef Plane<s32>	Planei;
	typedef Plane<f32>	Planef;
}

#endif