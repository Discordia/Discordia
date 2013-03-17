#include "OpenGLVertexBuffer.h"

namespace Discordia
{
	namespace Graphics
	{
		OpenGLVertexBuffer::OpenGLVertexBuffer(const u32& size)
			: IBufferObject(), size(size), isLocked(false)
		{
			glGenBuffers(1, &vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, size, 0, GL_DYNAMIC_DRAW);
		}

		OpenGLVertexBuffer::~OpenGLVertexBuffer()
		{
			glDeleteBuffers(1, &vertexBuffer);
		}

		void OpenGLVertexBuffer::Create(const u32& size)
		{
		}

		void OpenGLVertexBuffer::Resize(const u32& size)
		{
			// TODO: implement
			// Resize of buffer, invalidates all data that the buffer contains.
		}

		void* OpenGLVertexBuffer::Lock()
		{
			void *v;

			if (!isLocked) 
			{
				v = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
				isLocked = true;
			} 
			else 
				glGetBufferPointerv(GL_ARRAY_BUFFER, GL_BUFFER_MAP_POINTER, &v);

			return v;
		}

		bool OpenGLVertexBuffer::Unlock()
		{
			if (isLocked) 
			{
				if (!glUnmapBuffer(GL_ARRAY_BUFFER)) 
				{
					isLocked = false;
					return false;
				}
			}

			isLocked = false;
			return true;
		}

		void* OpenGLVertexBuffer::GetPointer()
		{
			void *pointer = 0;

			if (isLocked)
				glGetBufferPointerv(GL_ARRAY_BUFFER, GL_BUFFER_MAP_POINTER, &pointer);

			return pointer;
		}

		void OpenGLVertexBuffer::Update(const s32& offset, const u32& size, const void* data)
		{
			// Mayby should check that the buffer is ot mapped (locked).
			glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
		}


	}
}