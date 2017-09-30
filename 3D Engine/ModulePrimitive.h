#pragma once
#pragma once
#include "Module.h"

enum Type
{
	EMPTY = 0,
	TRIANGLE,
	CUBE_INDICE,
	CUBE
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
	void CreateCubeIndice();

	int array = 0;
	uint my_indices = 0;
};