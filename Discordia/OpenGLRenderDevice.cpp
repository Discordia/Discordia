#include "OpenGLVertexBuffer.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLRenderDevice.h"
#include "OpenGLResourceManager.h"

namespace Discordia
{
	namespace Graphics
	{
		OpenGLRenderDevice::OpenGLRenderDevice(const Dimension2D<s32>& windowDim, u16 bits, bool fullscreen, Logger* logger)
			: RenderDeviceStub(windowDim), logger(logger)
		{
			isActive = true;		
			this->windowDim = windowDim;
			this->bits = bits;
			this->fullscreen = fullscreen;

			videoFlags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE;

			if (videoInfo->hw_available)
				videoFlags |= SDL_HWSURFACE;
			else
				Destroy();

			if (videoInfo->blit_hw)
				videoFlags |= SDL_HWACCEL;
			else
				Destroy();

			if (fullscreen)
			{
				logger->Log("Going to fullscreen", LOG_DEBUG);
				videoFlags |= SDL_FULLSCREEN;
				SDL_ShowCursor(SDL_DISABLE);
			}

			SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
			surface = SDL_SetVideoMode(windowDim.width, windowDim.height, bits, videoFlags);

			if (!surface)
				Destroy();

			Init();
			SetViewportRelative(0, 0, 1, 1);

			// Create resourceManager
			resourceManager = new OpenGLResourceManager(logger);
		}

		OpenGLRenderDevice::~OpenGLRenderDevice()
		{
			if (resourceManager)
			{
				delete resourceManager;
				resourceManager = 0;
			}
		}

		void OpenGLRenderDevice::Resize(const Dimension2D<s32>& windowSize)
		{
			// TODO: error with resize, gets problem with glDrawRangeElements, 
			// access valation strange???
		}

		void OpenGLRenderDevice::Init()
		{
			glShadeModel(GL_SMOOTH);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClearDepth(1.0f);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);		

			// Setup lights
			// TODO: This should later be incorerated into the scenegraph
			//		 and not be so hardcoded as it is now.
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);

			// Light model parameters:
			GLfloat lmKa[] = {0.0, 0.0, 0.0, 0.0 };
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);

			glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
			glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

			// Lighting parameters:
			GLfloat light_pos[] = { 0.0, 5, 0, 1.0};
			GLfloat light_Ka[] = {0.4f, 0.4f, 0.4f, 1.0};
			GLfloat light_Kd[] = {0.6f, 0.6f, 0.6f, 1.0};
			GLfloat light_Ks[] = {1.0, 1.0, 1.0, 1.0};

			glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
			glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
			glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

			// Material parameters:
			GLfloat material_Ka[] = {0.8f, 0.8f, 0.8f, 1.0};
			GLfloat material_Kd[] = {0.8f, 0.8f, 0.8f, 1.0};
			GLfloat material_Ks[] = {0.8f, 0.8f, 0.8f, 1.0};
			GLfloat material_Ke[] = {0.1f, 0.1f, 0.1f, 0.0};
			GLfloat material_Se = 20.0;

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);

			// Initialize GLEE
			if (!GLeeInit())
				Destroy();

			// Create vertexBuffer and indexBuffer
			// TODO: How much memory should be allocated?
			// Should not be a parameter, should depend on systeminformation (VRAM size).

			if (!glBindBuffer || !GL_ARRAY_BUFFER || !GL_ELEMENT_ARRAY_BUFFER || !glDeleteBuffers ||
				!GL_WRITE_ONLY || !GL_BUFFER_MAP_POINTER || !glUnmapBuffer || !glMapBuffer ||
				!glGetBufferPointerv || !glBufferSubData)
			{
				logger->Log("Could not find extension GL_ARB_vertex_buffer_object", LOG_ERROR);
				return;
			}

			vertexBuffer = new OpenGLVertexBuffer(1400000);
			indexBuffer = new OpenGLIndexBuffer(1000000);
		}

		void OpenGLRenderDevice::BeginScene()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			matricies[MATRIX_WORLD].Identity();
			matricies[MATRIX_VIEW].Identity();
		}

		void OpenGLRenderDevice::EndScene()
		{
			SDL_GL_SwapBuffers();
		}

		void OpenGLRenderDevice::SetMatrix(MatrixState state, const Matrix4& matrix)
		{
			matricies[state] = matrix;
			f32* f = new f32[16];

			switch(state)
			{
				case MATRIX_WORLD:
				case MATRIX_VIEW:
					glMatrixMode(GL_MODELVIEW);
					glLoadMatrixf(matricies[MATRIX_WORLD]*matricies[MATRIX_VIEW]);
					break;

				case MATRIX_PROJECTION:
					glMatrixMode(GL_PROJECTION);
					glLoadMatrixf(matricies[MATRIX_PROJECTION]);
					glGetFloatv(GL_PROJECTION_MATRIX, f);
					glMatrixMode(GL_MODELVIEW);
					break;
			}
		}

		const Matrix4& OpenGLRenderDevice::GetMatrix(MatrixState state)
		{
			return matricies[state];
		}

		void OpenGLRenderDevice::SetTexture(const u32& stage, shared_ptr<ITexture> texture)
		{
			if (stage > 1)
				return;

			glEnable(GL_TEXTURE_2D); // Should mayby do this somewhere else, not everytime we need to bind a texture
			glActiveTexture(stage == 0 ? GL_TEXTURE0_ARB : GL_TEXTURE1_ARB);
			glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
		}

		void OpenGLRenderDevice::UnsetTexture()
		{
			glDisable(GL_TEXTURE_2D);
		}

		void OpenGLRenderDevice::DrawPrimitives(const u32& voffset, 
			const u32& nrVerticies,
			VertexFormat format,
			DrawMode drawMode)
		{
			glInterleavedArrays(GL_C3F_V3F, 0, BUFFER_OFFSET(voffset));
			glDrawArrays(GL_TRIANGLES, 0, nrVerticies);
		}

		void OpenGLRenderDevice::DrawIndexPrimitives(const u32& voffset, 
			const u32& ioffset, 
			const u32& vertexStart, 
			const u32& vertexEnd, 
			const u32& nrVerticies,
			VertexFormat format,
			DrawMode drawMode)
		{
			int verOff = voffset;

			// Enable vertex streams
			switch(format)
			{
			case VERTEX_COMPLETE:
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_COLOR_ARRAY);
				glEnableClientState(GL_NORMAL_ARRAY);

				glVertexPointer(3, GL_FLOAT, sizeof(VertexComplete),  BUFFER_OFFSET(verOff));
				verOff += sizeof(f32)*3;
				glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(VertexComplete), BUFFER_OFFSET(verOff));
				verOff += 4*sizeof(u8);
				glNormalPointer(GL_FLOAT, sizeof(VertexComplete), BUFFER_OFFSET(verOff));
				verOff += 3*sizeof(f32);

				// multitexturing
				// Texture stage 0
				glClientActiveTexture(GL_TEXTURE0);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glTexCoordPointer(2, GL_FLOAT, sizeof(VertexComplete), BUFFER_OFFSET(verOff));
				verOff += 2*sizeof(f32);

				// Texture stage 2
				glClientActiveTexture(GL_TEXTURE1);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glTexCoordPointer(2, GL_FLOAT, sizeof(VertexComplete), BUFFER_OFFSET(verOff));
				break;

			case VERTEX_PN2T:
				break;

			case VERTEX_PCNT:
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_COLOR_ARRAY);
				glEnableClientState(GL_NORMAL_ARRAY);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);

				glVertexPointer(3, GL_FLOAT, sizeof(VertexPCNT), BUFFER_OFFSET(verOff));
				verOff += 3*sizeof(f32);
				glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(VertexPCNT), BUFFER_OFFSET(verOff));
				verOff += 4*sizeof(u8);
				glNormalPointer(GL_FLOAT, sizeof(VertexPCNT), BUFFER_OFFSET(verOff));
				verOff += 3*sizeof(f32);
				glTexCoordPointer(2, GL_FLOAT, sizeof(VertexPCNT), BUFFER_OFFSET(verOff));
				break;

			case VERTEX_PT:
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glVertexPointer(3, GL_FLOAT, sizeof(VertexPT), BUFFER_OFFSET(verOff));
				verOff += 3* sizeof(f32);
				glTexCoordPointer(2, GL_FLOAT, sizeof(VertexPT), BUFFER_OFFSET(verOff));
				break;

			case VERTEX_PC:
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_COLOR_ARRAY);
				glVertexPointer(3, GL_FLOAT, 3*sizeof(f32) + 4*sizeof(u8), BUFFER_OFFSET(verOff));
				verOff += sizeof(f32)*3;
				glColorPointer(4, GL_UNSIGNED_BYTE, 3*sizeof(f32) + 4*sizeof(u8), BUFFER_OFFSET(verOff));
				break;

			case VERTEX_PCN:
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_COLOR_ARRAY);
				glEnableClientState(GL_NORMAL_ARRAY);

				glVertexPointer(3, GL_FLOAT, sizeof(VertexPCN), BUFFER_OFFSET(verOff));
				verOff += 3*sizeof(f32);
				glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(VertexPCN), BUFFER_OFFSET(verOff));
				verOff += 4*sizeof(u8);
				glNormalPointer(GL_FLOAT, sizeof(VertexPCN), BUFFER_OFFSET(verOff));
				break;

			case VERTEX_PNT:
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_NORMAL_ARRAY);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);

				glVertexPointer(3, GL_FLOAT, sizeof(VertexPNT), BUFFER_OFFSET(verOff));
				verOff += 3*sizeof(f32);
				glNormalPointer(GL_FLOAT, sizeof(VertexPNT), BUFFER_OFFSET(verOff));
				verOff += 3*sizeof(f32);
				glTexCoordPointer(2, GL_FLOAT, sizeof(VertexPNT), BUFFER_OFFSET(verOff));
				break;

			default:
				break;
			}

			// Draw 
			switch(drawMode)
			{
			case DRAW_WIREFRAME:
				glDrawRangeElements(GL_LINE_STRIP, vertexStart, vertexEnd, nrVerticies, GL_UNSIGNED_INT, BUFFER_OFFSET(ioffset));
				break;

			case DRAW_POLYGON:
				glDrawRangeElements(GL_TRIANGLES, vertexStart, vertexEnd, nrVerticies, GL_UNSIGNED_INT, BUFFER_OFFSET(ioffset));
				break;
			}

			// Disabel vertex streams
			switch(format)
			{
			case VERTEX_COMPLETE:
				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_COLOR_ARRAY);
				glDisableClientState(GL_NORMAL_ARRAY);
				glClientActiveTextureARB(GL_TEXTURE0_ARB);
				glDisableClientState ( GL_TEXTURE_COORD_ARRAY );
				glClientActiveTextureARB(GL_TEXTURE1_ARB);
				glDisableClientState ( GL_TEXTURE_COORD_ARRAY );
				break;

			case VERTEX_PN2T:
				break;

			case VERTEX_PCNT:
				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_COLOR_ARRAY);
				glDisableClientState(GL_NORMAL_ARRAY);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				break;

			case VERTEX_PT:
				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				break;

			case VERTEX_PC:
				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_COLOR_ARRAY);
				break;

			case VERTEX_PCN:
				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_COLOR_ARRAY);
				glDisableClientState(GL_NORMAL_ARRAY);
				break;

			case VERTEX_PNT:
				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_NORMAL_ARRAY);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				break;

			default:
				break;
			}
		}

		void OpenGLRenderDevice::SetViewportRelative(f32 xtop, f32 ytop, f32 xbottom, f32 ybottom)
		{
			glViewport((GLsizei)(xtop*windowDim.width), 
				(GLsizei)(ytop*windowDim.height), 
				(GLsizei)(xbottom*windowDim.width), 
				(GLsizei)(ybottom*windowDim.height));
		}

		IResourceManager* OpenGLRenderDevice::GetResourceManager()
		{
			return resourceManager;
		}

		void OpenGLRenderDevice::SetClipPlane(const Planef& plane)
		{
			GLdouble* p = new GLdouble[4];
			p[0] = plane.normal.x;
			p[1] = plane.normal.y;
			p[2] = plane.normal.z;
			p[3] = plane.D;
			glClipPlane(GL_CLIP_PLANE0, p);
			glEnable(GL_CLIP_PLANE0);
		}

		void OpenGLRenderDevice::UnsetClipPlane()
		{
			glDisable(GL_CLIP_PLANE0);
		}

		void OpenGLRenderDevice::SetLightPosition(const Vector3f& lightPos)
		{
			GLfloat lPos[] = {lightPos.x, lightPos.y, lightPos.z, 1};
			glLightfv(GL_LIGHT0, GL_POSITION, lPos);
		}

	}
}