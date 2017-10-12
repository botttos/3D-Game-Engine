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
	FRUSTUM
}; 

class GeometryBase
{
public:
	GeometryBase(GeomType t);
	virtual ~GeometryBase();

	virtual void Start();

	GeomType type;
	
};