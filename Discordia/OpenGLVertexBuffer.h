#ifndef OPENGL_VERTEX_BUFFER_H_INCLUDED
#define OPENGL_VERTEX_BUFFER_H_INCLUDED

#include <gl/GLee.h>
#include "IBufferObject.h"

namespace Discordia
{
	namespace Graphics
	{
		/**
		 *  An OpenGL vertex buffer, implemented with the GL_ARB_vertex_buffer_object extension.	
		 */
		class OpenGLVertexBuffer : public IBufferObject
		{
		public:
			OpenGLVertexBuffer(const u32& size);
			virtual ~OpenGLVertexBuffer();

			void Create(const u32& size);
			void Resize(const u32& size);

			void *Lock();
			bool Unlock();
			void *GetPointer();
			void Update(const s32& offset, const u32& size, const void* data);

			void Activate()		{ glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); }
			void Disable()		{ glBindBuffer(GL_ARRAY_BUFFER, 0); }

		private:
			u32		vertexBuffer;
			u32		size;
			bool	isLocked;
		};
	}
}

#endif