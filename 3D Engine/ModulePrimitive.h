#pragma once
#pragma once
#include "Module.h"
#include <stdlib.h> 
#include <vector>
#include "Glew\include\glew.h"
#include "GeometryBase.h"

using namespace std;

struct SpherePrim
{
public:
	SpherePrim();
	SpherePrim(int rings, int sectors, float radius);
	~SpherePrim();

	bool UpdateSph();

public:

	GeomType type = SPHERE;

	unsigned int rings = 10;
	unsigned int sectors = 10;
	float radius = 1;

	std::vector<GLfloat> sphere_vertices;
	std::vector<GLfloat> sphere_normals;
	std::vector<GLfloat> sphere_texcoords;
	std::vector<GLushort> sphere_indices;
};

class ModulePrimitive : public Module
{
public:

	ModulePrimitive(Application* app, bool start_enabled = true);
	~ModulePrimitive();

	bool Start();
	bool Update();
	bool CleanUp();

	void CreatePrimitive(GeomType primitive);

	bool SetType(GeomType type);
	std::vector<SpherePrim*> spheres;

private:

	void Triangle();
	void CubeVertex();
	void CubeIndice();
	void Cylinder();

};