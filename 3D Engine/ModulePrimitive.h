#pragma once
#pragma once
#include "Module.h"

enum Type
{
	CUBE = 0,
	TRIANGLE
};

class ModulePrimitive : public Module
{
public:

	ModulePrimitive(Application* app, bool start_enabled = true);
	~ModulePrimitive();

	bool Start();
	bool Update();
	bool CleanUp();

	bool SetType(int type);

private:
	int type;
	void CreateTriangle();
	void CreateCube();
};