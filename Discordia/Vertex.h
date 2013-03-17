#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED

#include "Color.h"
#include "Vector3.h"

/**
 *  In this file diffrent vertex formats are defined. Everyonme has a position, but then
 *  they can also have normal, color, and up to two texture stages.
 */

namespace Discordia
{
	namespace Graphics
	{
		enum VertexFormat
		{
			VERTEX_DEFAULT		= 1 << 0,
			VERTEX_COMPLETE		= 1 << 1,
			VERTEX_PN2T			= 1 << 2,
			VERTEX_PCNT			= 1 << 3,
			VERTEX_PT			= 1 << 4,
			VERTEX_PC			= 1 << 5,
			VERTEX_PCN			= 1 << 6,
			VERTEX_PNT			= 1 << 7
		};

		class VertexComplete
		{
		public:
			VertexComplete(Vector3f p, Color c, Vector3f n, Vector2f s1, Vector2f s2)
				: position(p), 
				  color(c),
				  normal(n),
				  stage1(s1),
				  stage2(s2) {};


			Vector3f position;
			Color    color;
			Vector3f normal;
			Vector2f stage1;
			Vector2f stage2;
		};


		class VertexPN2T
		{
			VertexPN2T(Vector3f p, Vector3f n, Vector2f s1, Vector2f s2)
				: position(p), 
				  normal(n),
				  stage1(s1),
				  stage2(s2) {};

			Vector3f position;
			Vector3f normal;
			Vector2f stage1;
			Vector2f stage2;
		};
	
		class VertexPCNT
		{
		public:
			VertexPCNT() {}
			VertexPCNT(Vector3f p, Color c, Vector3f n, Vector2f s1)
				: position(p), 
				  color(c),
				  normal(n),
				  stage1(s1) {};
			~VertexPCNT() {}

			Vector3f position;
			Color	 color;
			Vector3f normal;
			Vector2f stage1;
		};
		
		class VertexPT
		{
		public:
			VertexPT() {}
			VertexPT(Vector3f p, Vector2f s1)
				: position(p), 
				  stage1(s1) {};

			Vector3f position;
			Vector2f stage1;
		};
		
		class VertexPC
		{
		public:
			VertexPC() {}
			VertexPC(Vector3f p, Color c)
				: position(p),
				  color(c) {}

			Vector3f position;
			Color    color;
		};

		class VertexPCN
		{
		public:
			VertexPCN() {}
			VertexPCN(Vector3f p, Color c, Vector3f n)
				: position(p),
				  color(c),
				  normal(n) {}

		  Vector3f	position;
		  Color		color;
		  Vector3f	normal;
		};

		class VertexPNT
		{
		public:
			VertexPNT() {}
			VertexPNT(Vector3f p, Vector3f n, Vector2f s1)
				: position(p), normal(n), stage1(s1) {}

			Vector3f position;
			Vector3f normal;
			Vector2f stage1;
		};
		
	}
}


#endif