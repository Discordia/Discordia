#ifndef IGEOMETRY_NODE_H_INCLUDED
#define IGEOMETRY_NODE_H_INCLUDED

#include <memory>
#include <algorithm>
#include "ISceneNode.h"
#include "GeometryChunk.h"

using std::shared_ptr;

namespace Discordia
{
	namespace Scene
	{
		/**
		 *  Scene node that holds geometry.
		 */
		class IGeometryNode : public ISceneNode
		{
		public:
			IGeometryNode(ISceneNode* parent, const Matrix4& localTransform)
				: ISceneNode(parent, localTransform)
			{
			}

			virtual ~IGeometryNode()
			{
				vector<GeometryChunk* >::iterator chunkIt;

				for (chunkIt = chunks.begin(); chunkIt != chunks.end(); chunkIt++)
					delete *chunkIt;
			}

			void AddGeometryChunk(GeometryChunk* chunk)
			{
				// TODO: take in a shared_ptr?
				chunks.push_back(chunk);
			}

			void ClearAllGeometryChunks()
			{
				vector<GeometryChunk* >::iterator chunkIt;

				for (chunkIt = chunks.begin(); chunkIt != chunks.end(); chunkIt++)
					delete *chunkIt;
				
				chunks.clear();
			}

			virtual void BuildRenderQueue(const ViewFrustum* frustum, RenderQueue* renderQueue)
			{
				vector<GeometryChunk* >::iterator chunkIt;

				for (chunkIt = chunks.begin(); chunkIt != chunks.end(); chunkIt++)
					renderQueue->InsertChunk(*chunkIt);

				ISceneNode::BuildRenderQueue(frustum, renderQueue); 
			}

		protected:
			vector<GeometryChunk* > chunks;
		};
	}
}

#endif