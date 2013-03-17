#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include "Types.h"

namespace Discordia
{

	/* Buffer offset, used with vertex buffer object (VBO). */
	#define BUFFER_OFFSET(i) ((char *)0 + (i))

	/* Math constants */
	const f32 PI			= 3.14159f;
	const f64 RAD_TO_DEG	= 180.0 / 3.1415926535897932384626433832795;
	const f64 DEG_TO_RAD	= 3.1415926535897932384626433832795 / 180.0;
	const f32 EPSILON		= 1e-08f;

	class Utility
	{
	public:
		static f64 DegreeToRadian(f64 degree)
		{
			return degree / DEG_TO_RAD;
		}

		static f32 DegreeToRadianf(f32 degree)
		{
			return degree / (f32) DEG_TO_RAD;
		}

		static f64 RadianToDegree(f64 radian)
		{
			return radian / RAD_TO_DEG;
		}

		static f32 RadianToDegreef(f32 radian)
		{
			return radian / (f32) RAD_TO_DEG;
		}
			
	};
}

#endif