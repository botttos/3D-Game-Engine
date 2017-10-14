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

struct CubeIndicePrim
{
public:
	CubeIndicePrim();
	~CubeIndicePrim();

	bool UpdateCubeIndice();

public:
	GeomType type = CUBE_INDICE;

	std::vector<GLfloat> vertex;
	std::vector<GLfloat> indices;

	uint vertices_id = 0;
	uint indices_id = 0;
};

struct CylinderPrim
{
public:
	CylinderPrim();
	~CylinderPrim();

	bool UpdateCylinder();

public:
	GeomType type = CYLINDER;

	float radius = 1.0f;
	float height = 3.0f;
};

struct NormalCubePrim
{
public:
	NormalCubePrim();
	~NormalCubePrim();

	bool UpdateNormalCube();

public:
	GeomType type = CUBE;

	std::vector<GLfloat> vertex;
	uint vertices_id = 0; 
};


class ModulePrimitive : public Module
{
public:

	ModulePrimitive(bool start_enabled = true);
	~ModulePrimitive();

	bool Start();
	bool Update();
	bool CleanUp();

	void CreatePrimitive(GeomType primitive);

	std::vector<SpherePrim*> spheres;
	std::vector<CubeIndicePrim*> cubes_indices;
	std::vector<CylinderPrim*> cylinders;
	std::vector<NormalCubePrim*> normal_cubes;
private:

	void Triangle();
};


