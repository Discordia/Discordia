#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include "Types.h"
#include "Vertex.h"

namespace Discordia
{
	namespace Scene
	{
		/** 
		 *	Raw verticies and indicies.
		 */
		class Geometry
		{
		public:
			Geometry() : verticies(0), indicies(0) {}
			Geometry(s32 nrVertex, s32 nrIndicies)
			{
				verticies = new Graphics::VertexPNT[nrVertex];
				indicies = new u32[nrIndicies];
			}
			~Geometry()
			{
				if (verticies)
				{
					delete[] verticies;
					verticies = 0;
				}

				if (indicies)
				{
					delete[] indicies;
					indicies = 0;
				}
			}

			Graphics::VertexPNT*	verticies;
			u32*					indicies;
		};
	}
}

#endif