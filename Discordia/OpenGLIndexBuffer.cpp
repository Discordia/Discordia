#include "OpenGLIndexBuffer.h"

namespace Discordia
{
	namespace Graphics
	{
		OpenGLIndexBuffer::OpenGLIndexBuffer(const u32& size)
			: IBufferObject(), size(size), isLocked(false)
		{
			glGenBuffers(1, &indexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, 0, GL_DYNAMIC_DRAW);
		}

		OpenGLIndexBuffer::~OpenGLIndexBuffer()
		{
			glDeleteBuffers(1, &indexBuffer);
		}

		void OpenGLIndexBuffer::Create(const u32& size)
		{
		}

		void OpenGLIndexBuffer::Resize(const u32& size)
		{
			// TODO: implement
			// Resize of the buffer, invalidates any data that the buffer containes.
		}

		void* OpenGLIndexBuffer::Lock()
		{
			void *v;

			if (!isLocked) 
			{
				v = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
				isLocked = true;
			} 
			else 
				glGetBufferPointerv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_MAP_POINTER, &v);

			return v;
		}

		bool OpenGLIndexBuffer::Unlock()
		{
			if (isLocked) 
			{
				if (!glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER)) 
				{
					isLocked = false;
					return false;
				}
			}

			isLocked = false;
			return true;
		}

		void* OpenGLIndexBuffer::GetPointer()
		{
			void *v = 0;

			if (isLocked)
				glGetBufferPointerv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_MAP_POINTER, &v);

			return v;
		}

		void OpenGLIndexBuffer::Update(const s32& offset, const u32& size, const void* data)
		{
			// Mayby should check that the buffer is not mapped (locked).
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
		}
	}
}