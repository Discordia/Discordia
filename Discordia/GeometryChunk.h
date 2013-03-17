#ifndef GEOMETRY_CHUNK_H_INCLUDED
#define GEOMETRY_CHUNK_H_INCLUDED

#include <memory>
#include "Matrix4.h"
#include "Geometry.h"
#include "ITexture.h"

using std::shared_ptr;
using Discordia::Graphics::ITexture;

namespace Discordia
{
	namespace Scene
	{
		enum ShaderID
		{
			SHADER_NORMAL = 0,
			SHADER_NSE_WATER
		};

		/**
		 *  Geometry chunk holds geometry and info how the geometry should be rendered, and
		 *  if it's stored in VRAM (if so it's offset into vertex buffer and index buffer).
		 */
		class GeometryChunk
		{
		public:
			GeometryChunk(u32 shaderId, s32 nrVertex, s32 nrIndicies, shared_ptr<ITexture> texture)
				: shaderId(shaderId), inVRAM(false), nrVerticies(nrIndicies), voffset(0), ioffset(0), 
				  nrVertex(nrVertex), texture(texture)
			{
				geometry = new Geometry(nrVertex, nrIndicies);
			}

			GeometryChunk(u32 shaderId, s32 nrVertex, s32 nrIndicies)
				: shaderId(shaderId), inVRAM(false), nrVerticies(nrIndicies), nrVertex(nrVertex),
				voffset(0), ioffset(0)
			{
				geometry = new Geometry(nrVertex, nrIndicies);
			}

			GeometryChunk(Scene::Geometry* geometry, u32 shaderId) 
				: shaderId(shaderId), geometry(geometry), inVRAM(false), 
				nrVerticies(0), voffset(0), ioffset(0), nrVertex(0)
			{
			}

			~GeometryChunk() 
			{
				delete geometry;
			}

			// Info that should be in a VRAMCacheSlot
			u32 voffset;
			u32 ioffset;
			///////////////////////////////
			
			u32						nrVertex;
			u32						nrVerticies;
			u32						shaderId;
			shared_ptr<ITexture>	texture;
			bool					inVRAM;

			Geometry*				geometry;
			Matrix4					worldMatrix;
		};
	}
}

#endif