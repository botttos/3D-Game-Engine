#pragma once
#include "Module.h"
#include "Globals.h"
#include "GeometryBase.h"
#include <vector>


class ModuleFBX : public Module
{
public:

	ModuleFBX(bool start_enabled = true);
	virtual ~ModuleFBX();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	bool LoadFBX(const char* filename);

	uint GenerateTextureId(const char* path);

private:

	GeometryBase* m;
	std::vector<GeometryBase*> meshes;
};