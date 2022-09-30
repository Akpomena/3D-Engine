#include <Engine.h>
#include <Engine/Core/EntryPoint.h>
#include "./SandBoxLayer.h"

class SandBoxApplication : public Engine::Application
{
public:
	SandBoxApplication()
		:Application("SandBox")
	{
		SandBoxLayer* layer = new SandBoxLayer;
		PushLayer(layer);
	}
};

Engine::Application* Engine::createApplication()
{
	return new SandBoxApplication();
}