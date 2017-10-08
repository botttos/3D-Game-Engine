#pragma once
#include "Globals.h"

enum GeomType
{
	EMPTY = 0,
	TRIANGLE,
	CUBE_INDICE,
	CUBE_TEXTURIZED,
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
	float* vertices = nullptr;

};

class GeometryBase
{
public:
	GeometryBase(GeomType t);
	virtual ~GeometryBase();

	virtual void Start();
	bool Draw();

	ModelConfig object_mesh;
	GeomType type;
	
};