#ifndef IBUFFER_OBJECT_H_INCLUDED
#define IBUFFER_OBJECT_H_INCLUDED

#include "Utility.h"

namespace Discordia
{
	namespace Graphics
	{
		/**
		 *	Interface that encapsulate the ARB_GL_Vertex_Buffer_Object extension. Used 
		 *  for vertex buffer, and index buffer.
		 */
		class IBufferObject
		{
		public:
			virtual ~IBufferObject() {}
			virtual void Create(const u32& size) = 0;
			virtual void Resize(const u32& size) = 0;
			virtual void *Lock() = 0;
			virtual bool Unlock() = 0;
			virtual void *GetPointer() = 0;
			virtual void Update(const s32& offset, const u32& size, const void* data) = 0;
			virtual void Activate() = 0;
			virtual void Disable() = 0;

		protected:
			IBufferObject() {}
		};
	}
}

#endif