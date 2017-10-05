#pragma once
#include "Module.h"
#include "Globals.h"
#include "GeometryBase.h"
#include <vector>

class ModuleFBX : public Module
{
public:

	ModuleFBX(Application* app, bool start_enabled = true);
	virtual ~ModuleFBX();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	bool LoadFBX(const char* filename);

private:

	GeometryBase* m;
	std::vector<GeometryBase*> meshes;
};