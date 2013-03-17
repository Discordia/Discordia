#include "Discordia.h"
#include <memory>
#include <iostream>

using std::shared_ptr;
using std::weak_ptr;
using namespace Discordia;
using namespace Graphics;
using namespace Scene;

int main(int nArgs, char **args)
{
	shared_ptr<IDiscordiaDevice> device(CreateDevice());
	IRenderDevice* renderDevice = device->CreateRenderDevice(
												OPENGL_DEVICE, 
												Dimension2D<s32>(1024, 768), 
												32, 
												false);
	ISceneManager* sceneManager = device->GetSceneManager();

	// Set up scene
	sceneManager->AddBoxNode(Matrix4(), Vector3f(-1, -3, 1), Vector3f(0, 1, -21), "data/Crate.bmp"); // left
	sceneManager->AddBoxNode(Matrix4(), Vector3f(0, -3, 1), Vector3f(20, -2, -21), "data/Crate.bmp"); // bottom
	sceneManager->AddBoxNode(Matrix4(), Vector3f(0, -2, -20), Vector3f(20, 1, -21), "data/Crate.bmp"); // front
	sceneManager->AddBoxNode(Matrix4(), Vector3f(20, -3, 1), Vector3f(21, 1, -21), "data/Crate.bmp"); // right
	sceneManager->AddBoxNode(Matrix4(), Vector3f(0, -2, 1), Vector3f(20, 1, 0), "data/Crate.bmp"); // back
	sceneManager->AddBoxNode(Matrix4(), Vector3f(8, 0, -22), Vector3f(12, 15, -26), "data/Crate.bmp");
	sceneManager->AddBoxNode(Matrix4(), Vector3f(2, 0, -22), Vector3f(6, 15, -26), "data/Crate.bmp");
	sceneManager->AddNSEWaterNode(Matrix4(), Dimension2D<s32>(20, 20), 2, Vector2i(60, 60));

	// Render loop
	// The loop is layed out this way so that the scene is updated first and then rendered.
	// And we push alot of render comandos to the GPU and then while it's working we wait
	// with calling EndScene() (wait with swapping buffers) and update the scene instead for 
	// the next frame. This so that we use the CPU while the GPU is working, so that we achive 
	// some parallellism.
	while(!device->Run())
	{
		if (renderDevice->IsActive())
		{
			sceneManager->UpdateScene();
			renderDevice->EndScene();
			renderDevice->BeginScene();
			sceneManager->Draw();
		}
	}

	return 0;
}