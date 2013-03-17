#ifndef RENDER_QUEUE_H_INCLUDED
#define RENDER_QUEUE_H_INCLUDED

#include <vector>
#include "Types.h"
#include "GeometryChunk.h"

using std::vector;
using Discordia::Scene::GeometryChunk;

namespace Discordia
{
	namespace Shader
	{
		
		enum RenderPass
		{
			RENDER_PASS_FIRST = 0,
			RENDER_PASS_SECOND,
			RENDER_PASS_COUNT
		};

		/** 
		 *	Renderqueue, holds all geometry to be rendered in a frame, supports mulltiple apsses
		 *  (at the moment two9. Should be extened to supprt a undetermined amount of render passes,
		 *  and to be abvle to (radix-?)sort the geometry to minimize renderstate changes (most 
		 *  importently vertex/pixel shader changes and then texture changes).
		 */
		class RenderQueue
		{
		public:
			RenderQueue();
			~RenderQueue();

			void			InsertChunk(GeometryChunk* chunk);
			GeometryChunk*	GetChunk();
			bool			HasMore();
			s32				GetSize();
			void			SetRenderPass(RenderPass renderPass);
			void			Sort();
			void			Clear();

		private:
			vector<GeometryChunk* > renderQueue;
			RenderPass activePass;
			int passIndex;
		};
	}
}


#endif