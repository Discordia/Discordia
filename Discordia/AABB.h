#ifndef AABB_H_INCLUDED
#define AABB_H_INCLUDED

#include "Line.h"

namespace Discordia
{
	template<class T>
	class AxisAlignBoundBox
	{
	public:
		AxisAlignBoundBox() 
			: minCorner(-1, -1, -1), maxCorner(1, 1, 1) {}
		AxisAlignBoundBox(const Vector3<T>& min, const Vector3<T>& max)
			: minCorner(min), maxCorner(max) {}
		~AxisAlignBoundBox() {}

		void AddPoint(const Vector3f& point)
		{
			if (minCorner.x > point.x) minCorner.x = point.x;
			if (minCorner.y > point.y) minCorner.y = point.y;
			if (minCorner.z > point.z) minCorner.z = point.z;
			if (maxCorner.x < point.x) maxCorner.x = point.x;
			if (maxCorner.y < point.y) maxCorner.y = point.y;
			if (maxCorner.z < point.z) maxCorner.z = point.z;
		}

		// TODO: Should be replaced with the Plucker coordinates algorithm
		bool IntersectsLine(const Line<T>& line)
		{
			Vector3<T> middle = line.GetMiddle();
			Vector3<T> dir = line.GetDirection();
			dir.Normalize();
			f32 half = line.Length() * (T)0.5;

			const Vector3f e = (maxCorner - minCorner) * (T)0.5;
			const Vector3f t = (minCorner + e) - middle;
			float r;

			if ((fabs(t.x) > e.x + half * fabs(dir.x)) || 
				(fabs(t.y) > e.y + half * fabs(dir.y)) ||
				(fabs(t.z) > e.z + half * fabs(dir.z)) )
				return false;

			r = e.y * (T)fabs(dir.z) + e.z * (T)fabs(dir.y);
			if (fabs(t.y*dir.z - t.z*dir.y) > r )
				return false;

			r = e.x * (T)fabs(dir.z) + e.z * (T)fabs(dir.x);
			if (fabs(t.z*dir.x - t.x*dir.z) > r )
				return false;

			r = e.x * (T)fabs(dir.y) + e.y * (T)fabs(dir.x);
			if (fabs(t.x*dir.y - t.y*dir.x) > r)
				return false;

			return true;
		}

		Vector3<T> minCorner;
		Vector3<T> maxCorner; 
	};

	typedef AxisAlignBoundBox<f32> AABBf;
	typedef AxisAlignBoundBox<s32> AABBi;
}

#endif