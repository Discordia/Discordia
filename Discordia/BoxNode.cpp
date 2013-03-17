#include "BoxNode.h"

namespace Discordia
{
	namespace Scene
	{
		BoxNode::BoxNode(ISceneNode* parent, const Matrix4& localTransform, const Vector3f& minCorner, const Vector3f& maxCorner, shared_ptr<ITexture> texture)
			: IGeometryNode(parent, localTransform), minCorner(minCorner), maxCorner(maxCorner)
		{
			Vector3f* corners = new Vector3f[8];
			corners[0] = minCorner; 
			corners[1] = Vector3f(minCorner.x, minCorner.y, maxCorner.z); 
			corners[2] = Vector3f(minCorner.x, maxCorner.y, minCorner.z); 
			corners[3] = Vector3f(minCorner.x, maxCorner.y, maxCorner.z); 
			corners[4] = Vector3f(maxCorner.x, minCorner.y, maxCorner.z); 
			corners[5] = Vector3f(maxCorner.x, minCorner.y, minCorner.z); 
			corners[6] = maxCorner; 
			corners[7] = Vector3f(maxCorner.x, maxCorner.y, minCorner.z); 

			u32* indicies = new u32[36];
			indicies[0] = 0; indicies[1] = 1; indicies[2] = 2;
			indicies[3] = 2; indicies[4] = 1; indicies[5] = 3;
			indicies[6] = 4; indicies[7] = 5; indicies[8] = 6;
			indicies[9] = 6; indicies[10] = 5; indicies[11] = 7;
			indicies[12] = 5; indicies[13] = 0; indicies[14] = 7;
			indicies[15] = 7; indicies[16] = 0; indicies[17] = 2;
			indicies[18] = 1; indicies[19] = 4; indicies[20] = 3;
			indicies[21] = 3; indicies[22] = 4; indicies[23] = 6;
			indicies[24] = 0; indicies[25] = 5; indicies[26] = 1;
			indicies[27] = 1; indicies[28] = 5; indicies[29] = 4;
			indicies[30] = 3; indicies[31] = 6; indicies[32] = 2;
			indicies[33] = 2; indicies[34] = 6; indicies[35] = 7;

			Vector3f* normals = new Vector3f[6];
			normals[0].Set(-1, 0, 0); normals[1].Set(1, 0, 0);
			normals[2].Set(0, 0, 1); normals[3].Set(0, 0, -1);
			normals[4].Set(0, -1, 0); normals[5].Set(0, 1, 0);

			GeometryChunk* gc = new GeometryChunk(SHADER_NORMAL, 24, 36, texture);
			for (s32 i = 0, j = 0; i < 36; i+=6, j += 4)
			{
				gc->geometry->verticies[j].position.Set(corners[indicies[i]]);
			//	gc->geometry->verticies[j].color.Set(255, 255, 255, 255);
				gc->geometry->verticies[j].normal = normals[i/6];
				gc->geometry->verticies[j].stage1.Set(0, 0);
				gc->geometry->verticies[j+1].position.Set(corners[indicies[i+1]]);
			//	gc->geometry->verticies[j+1].color.Set(255, 255, 255, 255);
				gc->geometry->verticies[j+1].normal = normals[i/6];
				gc->geometry->verticies[j+1].stage1.Set(1, 0);
				gc->geometry->verticies[j+2].position.Set(corners[indicies[i+2]]);
			//	gc->geometry->verticies[j+2].color.Set(255, 255, 255, 255);
				gc->geometry->verticies[j+2].normal = normals[i/6];
				gc->geometry->verticies[j+2].stage1.Set(0, 1);
				gc->geometry->verticies[j+3].position.Set(corners[indicies[i+5]]);
			//	gc->geometry->verticies[j+3].color.Set(255, 255, 255, 255);
				gc->geometry->verticies[j+3].normal = normals[i/6];
				gc->geometry->verticies[j+3].stage1.Set(1, 1);

				gc->geometry->indicies[i]	= indicies[0] + j;
				gc->geometry->indicies[i+1]	= indicies[1] + j;
				gc->geometry->indicies[i+2]	= indicies[2] + j;
				gc->geometry->indicies[i+3]	= indicies[3] + j;
				gc->geometry->indicies[i+4]	= indicies[4] + j;
				gc->geometry->indicies[i+5]	= indicies[5] + j;
			}

			chunks.push_back(gc);
		}

		BoxNode::~BoxNode()
		{
		}
	}
}