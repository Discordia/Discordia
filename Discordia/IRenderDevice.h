#ifndef IRENDER_DEVICE_H_INCLUDED
#define IRENDER_DEVICE_H_INCLUDED

#include "RenderEnviorment.h"
#include "Dimension2D.h"
#include "IBufferObject.h"
#include "ResourceManager.h"
#include "ITexture.h"
#include "IGPUProgram.h"
#include "Matrix4.h"
#include "Vertex.h"
#include "SDL.h"


/**
 *  The render device is the main interface in the render system, takes care of all 
 *  the rendering with the help of the IBufferObject. Could either be a OpenGL, DirectX9 
 *  (when implemented) or a NULL device
 */

namespace Discordia
{
	namespace Graphics
	{
		enum DeviceType
		{
			OPENGL_DEVICE = 0,
			DIRECTX9_DEVICE,
			SOFTWARE_DEVICE,
			NULL_DEVICE
		};

		enum MatrixState
		{
			MATRIX_WORLD = 0,
			MATRIX_VIEW,
			MATRIX_PROJECTION,
			MATRIX_COUNT						
		};

		enum DrawMode
		{
			DRAW_WIREFRAME = 0,
			DRAW_POLYGON
		};

		class IRenderDevice
		{
		public:
			virtual ~IRenderDevice() {}

			virtual bool					RunEventLoop(SDL_Event event) = 0;
			virtual bool					IsActive() = 0;

			virtual void					Resize(const Dimension2D<s32>& windowSize) = 0;
			virtual void					Init() = 0;
			virtual const Dimension2D<s32>&	GetWindowDim() = 0;
			virtual void					SetViewportRelative(f32 xtop, f32 ytop, f32 xbottom, f32 ybottom) = 0;

			virtual IBufferObject*			GetVertexBuffer() = 0;
			virtual IBufferObject*			GetIndexBuffer() = 0;
			virtual IResourceManager*		GetResourceManager() = 0;
			virtual RenderEnviorment*		GetRenderEnviorment() = 0;
			virtual void					SetRenderEnviorment(RenderEnviorment* re) = 0;

			virtual void					BeginScene() = 0;
			virtual void					EndScene() = 0;

			virtual void					SetMatrix(MatrixState state, const Matrix4& matrix) = 0;
			virtual const Matrix4&			GetMatrix(MatrixState state) = 0;
			virtual void					SetTexture(const u32& stage, shared_ptr<ITexture> texture) = 0;
			virtual void					UnsetTexture() = 0;
 
			virtual void					DrawPrimitives(const u32& voffset, 
												const u32& nrVerticies,
												VertexFormat format,
												DrawMode drawMode = DRAW_POLYGON) = 0;
			virtual void					DrawIndexPrimitives(const u32& voffset, 
												const u32& ioffset, 
												const u32& vertexStart, 
												const u32& vertexEnd, 
												const u32& nrVerticies,
												VertexFormat format,
												DrawMode drawMode = DRAW_POLYGON) = 0;

			virtual void					SetClipPlane(const Planef& plane) = 0;
			virtual void					UnsetClipPlane() = 0;

			virtual void					UseBlending() = 0;
			virtual void					StopUsingBlending() = 0;

			virtual void					SetLightPosition(const Vector3f& lightPos) = 0;

		protected:
			IRenderDevice() {}
		};
	}
}

#endif