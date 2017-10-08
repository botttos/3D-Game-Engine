#pragma once
#pragma once
#include "Module.h"
#include <stdlib.h> 
#include <vector>
#include "Glew\include\glew.h"
#include "GeometryBase.h"

using namespace std;

class ModulePrimitive : public Module
{
public:

	ModulePrimitive(Application* app, bool start_enabled = true);
	~ModulePrimitive();

	bool Start();
	bool Update();
	bool CleanUp();

	bool SetType(GeomType type);

private:
	GeomType type;

	void Triangle();
	void CubeVertex();
	void CubeIndice();
	void CubeDirect();
	void Sphere();
	void Cylinder();

	GLuint texture;
	
	//Sphere
	std::vector<GLfloat> sphere_vertices;
	std::vector<GLfloat> sphere_normals;
	std::vector<GLfloat> sphere_texcoords;
	std::vector<GLushort> sphere_indices;
};