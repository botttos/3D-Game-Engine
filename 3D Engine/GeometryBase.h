#pragma once
#include "Globals.h"

enum GeomType
{
	EMPTY = 0,
	TRIANGLE,
	CUBE_INDICE,
	CUBE,
	SPHERE,
	CYLINDER,
	ARROW,
	AXIS,
	RAY,
	PLANE,
	CAPSULE,
	FRUSTUM,
	MESH
}; 


struct ModelConfig
{
	uint id_vertices = 0;
	uint num_indices = 0;
	uint* indices = nullptr;

	uint id_indices = 0;
	uint num_vertices = 0;
	uint* vertices = nullptr;

	uint id_normals = 0;
	uint num_normals = 0;
	float* normals = nullptr;

	uint id_uvs = 0;
	uint num_uvs = 0;
	float* uvs = nullptr;
};

class GeometryBase
{
public:
	GeometryBase(GeomType t);
	virtual ~GeometryBase();

	virtual void Start();

	ModelConfig object_mesh;
	GeomType type;
	
};