#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#include "Types.h"

namespace Discordia
{
	namespace Graphics
	{
		class Color
		{
		public:
			Color() {}
			Color(s32 r, s32 g, s32 b, s32 a)
				: color(((a & 0xff) << 24) | ((b & 0xff) << 16) | ((g & 0xff) << 8) | (r & 0xff)) {};
			Color(s32 c)
				: color(c) {};
			~Color() {};

			bool operator==(const Color& c) const 
			{ 
				return c.color == color; 
			}

			bool operator!=(const Color& c) const 
			{ 
				return c.color != color;
			}

			s32 getRed() const 
			{	
				return color & 0xff;	
			}

			s32 getGreen() const	
			{	
				return (color >> 8) & 0xff;	
			}

			s32 getBlue() const	
			{	
				return (color >> 16) & 0xff;	
			}

			s32 getAlpha() const	
			{	
				return (color >> 24) & 0xff;	
			}

			void setRed(s32 r) 
			{ 
				color = (((color >> 24) & 0xff) << 24) | (((color >> 16)& 0xff) << 16) | ((color >> 8 & 0xff) << 8) | (r & 0xff); 
			}

			void setGreen(s32 g) 
			{ 
				color = (((color >> 24) & 0xff) << 24) | (((color >> 16)& 0xff) << 16) | ((g & 0xff) << 8) | (color & 0xff);
			}

			void setBlue(s32 b) 
			{ 
				color = (((color >> 24) & 0xff)<<24) | ((b & 0xff) << 16) | ((color >> 8 & 0xff) << 8) | (color & 0xff); 
			}

			void setAlpha(s32 a) 
			{ 
				color = ((a & 0xff) << 24) | (((color >> 16)& 0xff) << 16) | ((color >> 8 & 0xff) << 8) | (color & 0xff); 
			}

			void Set(s32 r, s32 g, s32 b, s32 a) 
			{ 
				color = (((a & 0xff) << 24) | ((b & 0xff) << 16) | ((g & 0xff) << 8) | (r & 0xff)); 
			}

		public:
			s32 color;
		};
	}
}

#endif