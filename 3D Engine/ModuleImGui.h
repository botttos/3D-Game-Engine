#pragma once
#include "Module.h"

class ModuleImGui : public Module
{
public:
	ModuleImGui(bool start_enabled = true);
	~ModuleImGui();

	bool Start();
	update_status Update(float dt);
	update_status PreUpdate(float dt);
	bool Trigger(bool);
	bool CleanUp();

	void Inspector();

	bool able_imgui = true;

private:
	bool ImGuiUpdate();
};