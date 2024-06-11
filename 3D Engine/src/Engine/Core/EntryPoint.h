#pragma once

#include "../Debug/Instrumentor.h"

extern Engine::Application* Engine::createApplication();

int main(int argc, char** argv)
{
	PROFILE_BEGIN_SESSION("Startup", "Startup.json");
	auto app = Engine::createApplication();
	PROFILE_END_SESSION();

	PROFILE_BEGIN_SESSION("Running", "Running.json");
	app->run();
	PROFILE_END_SESSION();

	delete app;

	return 0;
}