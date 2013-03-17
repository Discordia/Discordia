#ifndef BOX_NODE_H_INCLUDED
#define BOX_NODE_H_INCLUDED

#include "IGeometryNode.h"

namespace Discordia
{
	namespace Scene
	{
		/** 
		 *	Scene geometry node that defines a box in 3d space.
		 */
		class BoxNode : public IGeometryNode
		{
		public:
			BoxNode(ISceneNode* parent, const Matrix4& localTransform, const Vector3f& minCorner, const Vector3f& maxCorner, shared_ptr<ITexture> texture);
			virtual ~BoxNode();

		protected:
			Vector3f minCorner;
			Vector3f maxCorner;
		};
	}
}


#endif