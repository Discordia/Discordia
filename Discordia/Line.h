#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED

#include "Types.h"

namespace Discordia
{
	template<class T>
	class Line
	{
	public:
		Line()
			: start(0, 0, 0), end(1, 1, 1) {};
		Line(Vector3<T>& s, const Vector3<T>& e)
			: start(s), end(e) {};
	
		Line(const Line<T>& line)
			: start(line.start), end(line.end) {};

		Line<T> operator+(const Vector3<T>& point) const 
		{ 
			return Line<T>(start + point, end + point); 
		};

		Line<T>& operator+=(const Vector3<T>& point) 
		{ 
			start += point; 
			end += point; 
			return *this; 
		};

		Line<T> operator-(const Vector3<T>& point) const 
		{ 
			return Line<T>(start - point, end - point); 
		};

		Line<T>& operator-=(const Vector3<T>& point) 
		{ 
			start -= point; 
			end -= point; 
			return *this; 
		};

		bool operator==(const Line<T>& other) const 
		{ 
			return (start==other.start && end==other.end) || (end==other.start && start==other.end);
		};

		bool operator!=(const Line<T>& other) const 
		{ 
			return !(start==other.start && end==other.end) || (end==other.start && start==other.end);
		};

		f32 Length()
		{
			return start.distanceTo(end);
		}

		Vector3<T> GetMiddle() const
		{
			return (start + end)*(T)0.5;
		}

		Vector3<T> GetDirection() const
		{
			return end - start;
		}

		Vector3<T> start;
		Vector3<T> end;
	};

	typedef Line<f32> Linef;
	typedef Line<s32> Linei;
}


#endif