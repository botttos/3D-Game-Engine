#pragma once
#include "Module.h"

class ModuleImGui : public Module
{
public:
	ModuleImGui(Application* app, bool start_enabled = true);
	~ModuleImGui();

	bool Start();
	update_status Update(float dt);
	update_status PreUpdate(float dt);
	bool Trigger(bool bolean);
	bool CleanUp();

	bool able_imgui = true;

private:
	bool ImGuiUpdate();
	bool blit_triangle = false;
	bool blit_cube = false;
};