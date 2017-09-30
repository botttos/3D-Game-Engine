#pragma once
#pragma once
#include "Module.h"
#include <stdlib.h> 
#include <vector>
#include "Glew\include\glew.h"

using namespace std;

enum Type
{
	EMPTY = 0,
	TRIANGLE,
	CUBE_INDICE,
	CUBE,
	SPHERE
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
	void Triangle();
	void CubeVertex();
	void CubeIndice();
	void Sphere();
	
	//Sphere
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> texcoords;
	std::vector<GLushort> indices;
};