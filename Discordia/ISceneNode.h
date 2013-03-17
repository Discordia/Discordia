#ifndef ISCENE_NODE_H_INCLUDED
#define ISCENE_NODE_H_INCLUDED

#include <vector>
#include <algorithm>
#include <memory>
#include "Matrix4.h"
#include "RenderQueue.h"
#include "ViewFrustum.h"
#include "AABB.h"

using std::vector;
using std::find;
using std::shared_ptr;
using Discordia::Shader::RenderQueue;

namespace Discordia
{
	namespace Scene
	{
		/**
		 *  Base class for scene nodes, base of scene graph.
		 */
		class ISceneNode
		{
		public:
			ISceneNode(ISceneNode* parent, const Matrix4& localTransform)
				: parent(parent), localMatrix(localTransform)
			{
				UpdateWorldMatrix();
			}

			virtual ~ISceneNode()
			{
			}

			void Update(const Matrix4& matrix)
			{
				// Update matrix
				UpdateWorldMatrix();

				// Update this node
				Update();

				// Continue down...
				vector<shared_ptr<ISceneNode> >::iterator it;

				for (it = children.begin(); it != children.end(); it++)
					(*it)->Update();

				// Update bounding volume (AABB)
			}

			virtual void BuildRenderQueue(const ViewFrustum* frustum, RenderQueue* renderQueue)
			{
				// TODO: Frustum Culling
				vector<shared_ptr<ISceneNode> >::iterator it;

				for (it = children.begin(); it != children.end(); it++)
					(*it)->BuildRenderQueue(frustum, renderQueue);
			}

			void PickNode(const Linef& ray)
			{
				vector<shared_ptr<ISceneNode> >::iterator it;

				for (it = children.begin(); it != children.end(); it++)
				{
					// Check child aabb agains ray
					(*it)->Pick(ray);
				}
			}

			virtual void Update() {}
			virtual void Pick(const Linef& ray) {}

			void AddChild(ISceneNode* child)
			{
				children.push_back(shared_ptr<ISceneNode>(child));
			}

			void RemoveChild(ISceneNode* child)
			{
				vector<shared_ptr<ISceneNode> >::iterator childIt;
				childIt = find(children.begin(), children.end(), shared_ptr<ISceneNode>(child));
				childIt = children.erase(childIt);
			}

			const Matrix4& GetWorldMatrix() const
			{
				return worldMatrix;
			}

			const Matrix4& GetLocalMatrix() const
			{
				return localMatrix;
			}

			virtual const AABBf& GetAABoundBox() const
			{
				return aabb;
			}

		protected:
			void UpdateWorldMatrix()
			{
				if (parent)
					worldMatrix = parent->GetWorldMatrix()*localMatrix;
				else
					worldMatrix = localMatrix;
			}

		protected:
			vector<shared_ptr<ISceneNode> > children;
			Matrix4 localMatrix;
			Matrix4 worldMatrix;
			ISceneNode* parent;
			AABBf aabb;
		};
	}
}

#endif