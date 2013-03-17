#ifndef OPENGL_RENDER_DEVICE_H_INCLUDED
#define OPENGL_RENDER_DEVICE_H_INCLUDED

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>	
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include "BitmapLoaderGLAux.h"
#endif

#include "RenderDeviceStub.h"
#include "Logger.h"

namespace Discordia
{
	namespace Graphics
	{
		/**
		 *  OpenGL render device, lightweight render implemented with OpenGL. Don't now anything
		 *  about the scene or whats in the vertex/index buffers, just renders what you store in
		 *  the vertex/index buffers and tell it to render.
		 *  TODO: Should not create vertex/index buffer here.Should be done in resourc manager.
		 */
		class OpenGLRenderDevice : public RenderDeviceStub
		{
		public:
			OpenGLRenderDevice(const Dimension2D<s32>& windowDim, u16 bits, bool fullscreen, Logger* logger);
			virtual ~OpenGLRenderDevice();

			void					Init();
			void					Resize(const Dimension2D<s32>& windowSize);
			void					BeginScene();
			void					EndScene();
			
			IResourceManager*		GetResourceManager();
			void					SetMatrix(MatrixState state, const Matrix4& matrix);
			const Matrix4&			GetMatrix(MatrixState state);
			void					SetTexture(const u32& stage, shared_ptr<ITexture> texture);
			void					UnsetTexture();

			const Dimension2D<s32>& GetWindowDim() { return windowDim; }
			void					SetViewportRelative(f32 xtop, f32 ytop, f32 xbottom, f32 ybottom);

			void					DrawPrimitives(const u32& voffset, 
										const u32& nrVerticies,
										VertexFormat format,
										DrawMode drawMode = DRAW_POLYGON);
			void					DrawIndexPrimitives(const u32& voffset, 
										const u32& ioffset, 
										const u32& vertexStart, 
										const u32& vertexEnd, 
										const u32& nrVerticies,
										VertexFormat format,
										DrawMode drawMode = DRAW_POLYGON);

			void					SetClipPlane(const Planef& plane);
			void					UnsetClipPlane();

			void					UseBlending() { glEnable(GL_BLEND); }
			void					StopUsingBlending() { glDisable(GL_BLEND); }
			void					SetLightPosition(const Vector3f& lightPos);

		protected:
			Logger* logger;
		};
	}
}



#endif