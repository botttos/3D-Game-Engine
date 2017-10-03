#pragma once

#include "Module.h"

class ModuleFBX : public Module
{
public:
	ModuleFBX(Application* app, bool start_enabled = true);
	~ModuleFBX();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
};