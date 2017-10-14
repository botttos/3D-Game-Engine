#pragma once
#include "Globals.h"

enum BaseGeomType
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
	GeometryBase(BaseGeomType t);
	virtual ~GeometryBase();

	virtual void Start();

	BaseGeomType type;
	
};