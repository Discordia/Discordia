#include "ShaderSystem.h"
#include "GeometryChunk.h"

using Discordia::Scene::GeometryChunk;

/**
 * Extremlly ugly special case implemeation just to get the demo running. The ShaderSystem is
 * supposed to be much more genral than this. Should implement something like YannL:s shader 
 * system that has been talked on www.gamedev.net. 
 * Reference: http://www.gamedev.net/community/forums/topic.asp?topic_id=169710
 */

namespace Discordia
{
	namespace Shader
	{
		ShaderSystem::ShaderSystem(Graphics::IRenderDevice* renderDevice, Graphics::IResourceManager* resourceManager)
			: IShaderSystem(), renderDevice(renderDevice), resourceManager(resourceManager), renderCamera(0),
			  globalVOffset(0), globalIOffset(0)
		{
			renderQueue = new RenderQueue();
			vertexBuffer = renderDevice->GetVertexBuffer();
			indexBuffer = renderDevice->GetIndexBuffer();

			// Setup water shaders
			weak_ptr<IShaderObject> vertexShader = resourceManager->GetVertexShader("data/water.vert");
			weak_ptr<IShaderObject> pixelShader  = resourceManager->GetPixelShader("data/water.frag");
			weak_ptr<IGPUProgram> gpuProgram = resourceManager->GetGPUProgram("WaterProgram");

			shared_ptr<IShaderObject> vShader = vertexShader.lock();
			shared_ptr<IShaderObject> pShader = pixelShader.lock();
			program = gpuProgram.lock();

			program->AttachShader(vShader);
			program->AttachShader(pShader);
			program->LinkProgram();
		}

		ShaderSystem::~ShaderSystem()
		{
		}

		RenderQueue* ShaderSystem::GetRenderQueue()
		{
			renderQueue->Clear();

			return renderQueue;
		}

		void ShaderSystem::SetRenderCamera(Scene::ICamera* camera)
		{
			renderCamera = camera;
			Dimension2D<s32> windowSize = renderDevice->GetWindowDim();
			f32 aspect = (f32) windowSize.width / windowSize.height;
			camera->SetAspectRation(aspect);
			renderDevice->SetMatrix(Graphics::MATRIX_PROJECTION, camera->GetProjectionMatrix());
		}

		void ShaderSystem::DrawRenderQueue()
		{
			renderDevice->SetMatrix(Graphics::MATRIX_VIEW, renderCamera->GetViewMatrix());
			renderDevice->SetLightPosition(Vector3f(0, 5, 0));

			while (renderQueue->HasMore())
			{
				GeometryChunk* chunk = renderQueue->GetChunk();

				if (chunk->shaderId == Scene::SHADER_NSE_WATER)
				{

					/*
					if (!pbuffer)
					{
						// For render to texture
						pbuffer = shared_ptr<IPixelBuffer>(resourceManager->CreateNewPixelBuffer(Dimension2D<s32>(1024, 1024)));
						dynamicTexture = resourceManager->CreateNewTexture(Dimension2D<s32>(1024, 1024));
					}

					// Render mirrored (and clipped) scene to texture
					if (pbuffer->SetBufferAsRenderTarget())
					{
						renderQueue->SetRenderPass(RENDER_PASS_SECOND);
						renderDevice->BeginScene();
						renderDevice->SetMatrix(Graphics::MATRIX_PROJECTION, renderCamera->GetProjectionMatrix());
						renderDevice->SetMatrix(Graphics::MATRIX_VIEW, renderCamera->GetViewMatrix());
						renderDevice->SetLightPosition(Vector3f(0, -5, 0));

						// Setup mirror matrix
						f32 m[] = {1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
						Matrix4 mirrorMatrix(m);
						renderDevice->SetMatrix(Graphics::MATRIX_WORLD, mirrorMatrix);
						renderDevice->SetClipPlane(Planef());

						// Bind VBO:s in the new render context
						vertexBuffer->Activate();
						indexBuffer->Activate();

						// Render to texture
						while (renderQueue->HasMore())
						{
							GeometryChunk* chunk2 = renderQueue->GetChunk();

							if (chunk2->shaderId != Scene::SHADER_NSE_WATER)
								RenderChunk(chunk2);
						}

						// Done rendering to texture
						// Mark: no renderDevice->EndScene(), we dont use double buffering with the pixel buffer
						
						renderDevice->UnsetClipPlane();
						pbuffer->SetWindowAsRenderTarget();
						renderQueue->SetRenderPass(RENDER_PASS_FIRST);

						renderDevice->SetMatrix(Graphics::MATRIX_PROJECTION, renderCamera->GetProjectionMatrix());
						renderDevice->SetMatrix(Graphics::MATRIX_VIEW, renderCamera->GetViewMatrix());
						renderDevice->SetMatrix(Graphics::MATRIX_WORLD, Matrix4());
					} */
				}

				RenderChunk(chunk);
			}
		}

		void ShaderSystem::RenderChunk(GeometryChunk* chunk)
		{
			// Is the geometry saved in VRAm, if not do save it in VRAM..
			if (!chunk->inVRAM)
			{
				chunk->voffset = globalVOffset;
				globalVOffset += chunk->nrVertex*sizeof(Graphics::VertexPNT);
				chunk->ioffset = globalIOffset*sizeof(u32);
				globalIOffset += chunk->nrVerticies;

				vertexBuffer->Update(chunk->voffset, sizeof(Graphics::VertexPNT)*chunk->nrVertex, chunk->geometry->verticies);
				indexBuffer->Update(chunk->ioffset, sizeof(u32)*chunk->nrVerticies, chunk->geometry->indicies);

				chunk->inVRAM = true;
			} // The water geometry is uppdated all the time, the index stay fixed
			else if (chunk->shaderId == Scene::SHADER_NSE_WATER) 
				vertexBuffer->Update(chunk->voffset, sizeof(Graphics::VertexPNT)*chunk->nrVertex, chunk->geometry->verticies);


			if (chunk->shaderId == Scene::SHADER_NORMAL)
			{
				renderDevice->SetTexture(0, chunk->texture);
			}
			else if (chunk->shaderId == Scene::SHADER_NSE_WATER)
			{
	//			if (pbuffer && dynamicTexture)
				{
					// Calculate projective texturing matrix = Mpt * Mp * Mc
					f32 m[] = {0.5f, 0, 0, 0, 0, 0.5f, 0, 0, 0, 0, 0.5f, 0, 0.5f, 0.5f, 0.5f, 1};
					Matrix4 matrixTemp(m);
					Matrix4 projMatrix = renderCamera->GetViewMatrix() * renderCamera->GetProjectionMatrix() * matrixTemp;

					// Use vertex and pixel shaders to do perspective texturing
					program->Begin();
					program->SendUniformMatrix4fv("projMatrix", 1, false, projMatrix.matrix);
					program->SendUniform1i("reflectTex", 0);
		//			renderDevice->SetTexture(0, dynamicTexture);
		//			pbuffer->BindBufferToTexture();
					renderDevice->UseBlending(); // Alpha blend water
				} 
			} 

			renderDevice->DrawIndexPrimitives(chunk->voffset, chunk->ioffset, 0, chunk->nrVertex, chunk->nrVerticies, Graphics::VERTEX_PNT);

			if (chunk->shaderId == Scene::SHADER_NSE_WATER)
			{
				renderDevice->StopUsingBlending();
			//	pbuffer->ReleaseBufferFromTexture(); 
				program->End();
			} 
		}

	}
}