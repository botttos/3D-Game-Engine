#include "GeometryBase.h"
#include "GLEW\include\glew.h"

GeometryBase::GeometryBase(BaseGeomType type) : type(type)
{}

GeometryBase::~GeometryBase()
{

}

void GeometryBase::Start()
{}