#pragma once

extern Engine::Application* Engine::createApplication();

int main(int argc, char** argv)
{

	auto app = Engine::createApplication();
	app->run();
	delete app;

	return 0;
}