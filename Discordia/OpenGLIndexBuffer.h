#ifndef OPENGL_INDEX_BUFFER_H_INCLUDED
#define OPENGL_INDEX_BUFFER_H_INCLUDED

#include <gl/GLee.h>
#include "IBufferObject.h"

namespace Discordia
{
	namespace Graphics
	{	
		/*
		*  OpenGL index buffer, implemented with the GL_ARB_vertex_buffer_object extension.	
		*/
		class OpenGLIndexBuffer : public IBufferObject
		{
		public:
			OpenGLIndexBuffer(const u32& size);
			virtual ~OpenGLIndexBuffer();
			
			void Create(const u32& size);
			void Resize(const u32& size);

			void *Lock();
			bool Unlock();
			void *GetPointer();
			void Update(const s32& offset, const u32& size, const void* data);

			void Activate()		{ glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer); }
			void Disable()		{ glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
			
		private:
			u32		indexBuffer;
			u32		size;
			bool	isLocked;
		};
	}
}

#endif