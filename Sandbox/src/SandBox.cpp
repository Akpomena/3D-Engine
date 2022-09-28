#include <Engine.h>
#include <Engine/Core/EntryPoint.h>

class SandBoxApplication : public Engine::Application
{
public:
	SandBoxApplication()
		:Application("SandBox")
	{
		
	}
};

Engine::Application* Engine::createApplication()
{
	return new SandBoxApplication();
}