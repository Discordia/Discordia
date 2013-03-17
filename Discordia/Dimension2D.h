#ifndef DIMENSION2D_H_INCLUDED
#define DIMENSION2D_H_INCLUDED

namespace Discordia
{
	template <class T>
	class Dimension2D 
	{
	public:

		Dimension2D()
			: width(0), height(0) {};

		Dimension2D(T width, T height)
			: width(width), height(height) {};

		Dimension2D(const Dimension2D<T>& other)
			: width(other.width), height(other.height) {};

		bool operator==(const Dimension2D<T>& other) const
		{
			return width == other.width && height == other.height;
		}


		bool operator!=(const Dimension2D<T>& other) const
		{
			return width != other.width || height != other.height;
		}

		const Dimension2D<T>& operator=(const Dimension2D<T>& other) 
		{
			width = other.width;
			height = other.height; 
			return *this;
		}

		T width;
		T height;
	};
}

#endif