#pragma once

#include "Module.h"
#include <string>

struct ModelConfig
{
	uint id_vertices = 0;
	uint num_indices = 0;
	uint* indices = nullptr;

	uint id_indices = 0;
	uint num_vertices = 0;
	float* vertices = nullptr;
};

class ModuleFBX : public Module
{
public:
	ModuleFBX(Application* app, bool start_enabled = true);
	~ModuleFBX();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void LoadFBX(std::string file_name);
};