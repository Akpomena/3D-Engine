#pragma once

#include <Engine.h>

class SandBoxLayer: public Engine::Layer
{
public:
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(float ts) override;
	virtual void OnEvent(Event& event) override;
	virtual void OnImGuiRender() override;
};

