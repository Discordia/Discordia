#include "OpenGLResourceManager.h"
#include "GLSlangPixelShader.h"
#include "GLSlangVertexShader.h"
#include "OpenGLTexture.h"
#include "GLSlangProgram.h"
#include "Win32OGLPixelBuffer.h"


//////TEMP ////////////////////
// TODO: Should not load bitmaps here, should be done in BMPCodec
#include "Surface.h"
#include "BitmapLoaderGLAux.h"
///////////////// TEMP //////////////////77


namespace Discordia
{
	namespace Graphics
	{
		IPixelBuffer* CreatePixelBuffer(const Dimension2D<s32>& pbufferDim);

		OpenGLResourceManager::OpenGLResourceManager(Logger* logger)
			: ResourceManager(), logger(logger)
		{
		}

		OpenGLResourceManager::~OpenGLResourceManager()
		{
		}

		weak_ptr<ITexture> OpenGLResourceManager::GetTexture(string fileName)
		{
			weak_ptr<ITexture> storedTexture(GetStoredTexture(fileName));

			// If texture was not currently loaded, load it and store it
			if (storedTexture.expired())
			{
				// TODO: should it be opened as a binary file????
				IO::IFileReader* fileReader = fileSystem->OpenReadOnly(fileName);
				weak_ptr<ITexture> texture(CreateTextureFromFile(fileReader));
				return texture;
			}

			// Return stored textue
			return storedTexture;
		}

		shared_ptr<ITexture> OpenGLResourceManager::CreateNewTexture(const Dimension2D<s32>& textureDim)
		{
			shared_ptr<ITexture> texture(new OpenGLTexture(textureDim));
			return texture;
		}

		weak_ptr<IGPUProgram> OpenGLResourceManager::GetGPUProgram(string programName)
		{

			// Ugly error checking, extension checking should be done at engine startup
			// and if something si not supported it should never be sued, and then
			// this ugly code should not need to be here.
			if (!GLEE_ARB_shading_language_100)
			{
				logger->Log("Didn't find extension GL_ARG_shading_language", LOG_ERROR);
				return weak_ptr<IGPUProgram>(shared_ptr<IGPUProgram>());
			}
			else if (!glCreateProgramObjectARB || !glDeleteObjectARB || !glUseProgramObjectARB ||
				!glCreateShaderObjectARB || !glShaderSourceARB || !glCompileShaderARB || !glGetObjectParameterivARB ||
				!glAttachObjectARB || !glGetInfoLogARB || !glLinkProgramARB || !glGetUniformLocationARB ||
				!glUniform4fARB || !glUniform1iARB)
			{
				logger->Log("Didn't find one or more extensions needed for GLSL", LOG_ERROR);
				return weak_ptr<IGPUProgram>(shared_ptr<IGPUProgram>());
			}

			weak_ptr<IGPUProgram> storedProgram(GetStoredProgram(programName));

			if (storedProgram.expired())
			{
				shared_ptr<IGPUProgram> program(new GLSlangProgram());
				programs.insert(std::make_pair(programName, program));
				weak_ptr<IGPUProgram> wpProgram(program);
				return wpProgram;
			}

			return storedProgram;
		}

		weak_ptr<IShaderObject> OpenGLResourceManager::GetVertexShader(string fileName)
		{
			if (!GLEE_ARB_shading_language_100)
			{
				logger->Log("Didn't find extension GL_ARG_shading_language", LOG_ERROR);
				return weak_ptr<IShaderObject>(shared_ptr<IShaderObject>());
			}
			else if (!glCreateProgramObjectARB || !glDeleteObjectARB || !glUseProgramObjectARB ||
				!glCreateShaderObjectARB || !glShaderSourceARB || !glCompileShaderARB || !glGetObjectParameterivARB ||
				!glAttachObjectARB || !glGetInfoLogARB || !glLinkProgramARB || !glGetUniformLocationARB ||
				!glUniform4fARB || !glUniform1iARB)
			{
				logger->Log("Didn't find one or more extensions needed for GLSL", LOG_ERROR);
				return weak_ptr<IShaderObject>(shared_ptr<IShaderObject>());
			}

			weak_ptr<IShaderObject> storedShader(GetStoredShader(fileName));
	
			if (storedShader.expired())
			{
				IO::IFileReader* fileReader = fileSystem->OpenReadOnly(fileName);
				shared_ptr<IShaderObject> shader(new GLSlangVertexShader());
				shader->Compile(fileReader);
				shaders.insert(std::make_pair(fileReader->GetFileName(), shader));
				weak_ptr<IShaderObject> wpShader(shader);
				return wpShader;
			}

			return storedShader;
		}

		weak_ptr<IShaderObject> OpenGLResourceManager::GetPixelShader(string fileName)
		{
			if (!GLEE_ARB_shading_language_100)
			{
				logger->Log("Didn't find extension GL_ARG_shading_language", LOG_ERROR);
				return weak_ptr<IShaderObject>(shared_ptr<IShaderObject>());
			}
			else if (!glCreateProgramObjectARB || !glDeleteObjectARB || !glUseProgramObjectARB ||
				!glCreateShaderObjectARB || !glShaderSourceARB || !glCompileShaderARB || !glGetObjectParameterivARB ||
				!glAttachObjectARB || !glGetInfoLogARB || !glLinkProgramARB || !glGetUniformLocationARB ||
				!glUniform4fARB || !glUniform1iARB)
			{
				logger->Log("Didn't find one or more extensions needed for GLSL", LOG_ERROR);
				return weak_ptr<IShaderObject>(shared_ptr<IShaderObject>());
			}

			weak_ptr<IShaderObject> storedShader(GetStoredShader(fileName));

			if (storedShader.expired())
			{
				IO::IFileReader* fileReader = fileSystem->OpenReadOnly(fileName);
				shared_ptr<IShaderObject> shader(new GLSlangPixelShader());
				shader->Compile(fileReader);
				shaders.insert(std::make_pair(fileReader->GetFileName(), shader));
				weak_ptr<IShaderObject> wpShader(shader);
				return wpShader;
			}

			return storedShader;
		}

		shared_ptr<IPixelBuffer> OpenGLResourceManager::CreateNewPixelBuffer(const Dimension2D<s32>& pbufferDim)
		{
			if (!wglReleasePbufferDCARB || !wglDestroyPbufferARB || !wglChoosePixelFormatARB ||
				!wglCreatePbufferARB || !wglGetPbufferDCARB || !wglQueryPbufferARB || !wglBindTexImageARB ||
				!wglReleaseTexImageARB)
			{
				logger->Log("Couldn't find WGL_EXT_pbuffer extension", LOG_ERROR);
				return shared_ptr<IPixelBuffer>();
			}

			shared_ptr<IPixelBuffer> pbuffer(CreatePixelBuffer(pbufferDim));
			pbuffer->Create();

			return pbuffer;
		}

		weak_ptr<ITexture> OpenGLResourceManager::CreateTextureFromFile(IO::IFileReader* fileReader)
		{
			ISurface* surface;

			if (fileReader->GetFileName().substr(fileReader->GetFileName().length()-4) == ".bmp")
			{
				// Laod bmp with glaux.
				// TODO: should implement bmp loader, i.e BMPCodec...
				AUX_RGBImageRec* bitmap = auxDIBImageLoad(fileReader->GetFileName().c_str());
				surface = new Surface(COLOR_R8G8B8, Dimension2D<s32>(bitmap->sizeX, bitmap->sizeY), bitmap->data); 
			}
			else
				surface = surfaceLoader->LoadSurface(fileReader);

			// Error with surface loader
			// Hopefully we will never get here and execute the ugly code
			if (!surface)
				return weak_ptr<ITexture>();

			// Create a new texture from the loaded surface and store it in
			// our texture cache (hash_map).
			shared_ptr<ITexture> textureEntry(new OpenGLTexture(surface));
			weak_ptr<ITexture> texture(textureEntry);
			textures[fileReader->GetFileName()] = textureEntry;

			delete surface;
			surface = 0;

			return texture;
		}

	}
}