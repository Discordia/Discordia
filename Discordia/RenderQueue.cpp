#include "RenderQueue.h"

namespace Discordia
{
	namespace Shader
	{
		RenderQueue::RenderQueue()
		{
			Clear();
		}

		RenderQueue::~RenderQueue()
		{
		}

		void RenderQueue::InsertChunk(GeometryChunk* chunk)
		{
			renderQueue.push_back(chunk);
		}

		GeometryChunk* RenderQueue::GetChunk()
		{
			return renderQueue[passIndex++];
		}

		bool RenderQueue::HasMore()
		{
			return passIndex < renderQueue.size();
		}

		s32 RenderQueue::GetSize()
		{
			return (s32)renderQueue.size();
		}

		void RenderQueue::SetRenderPass(RenderPass renderPass)
		{
			activePass = renderPass;
			// passIndex = 0;
		}

		void RenderQueue::Sort()
		{
		}

		void RenderQueue::Clear()
		{
			renderQueue.clear();

			activePass = RENDER_PASS_FIRST;
			passIndex = 0;
		}
	}
}