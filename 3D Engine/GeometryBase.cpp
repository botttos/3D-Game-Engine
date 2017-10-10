#include "GeometryBase.h"
#include "GLEW\include\glew.h"

GeometryBase::GeometryBase(GeomType type) : type(type)
{}

GeometryBase::~GeometryBase()
{
	delete[] object_mesh.indices;
	delete[] object_mesh.vertices;
}

void GeometryBase::Start()
{
	//Vertices Buffer
	glGenBuffers(1, (GLuint*) &(object_mesh.id_vertices));
	glBindBuffer(GL_ARRAY_BUFFER, object_mesh.id_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*object_mesh.num_vertices * 3, object_mesh.vertices, GL_STATIC_DRAW);

	//Indices Buffer
	glGenBuffers(1, (GLuint*) &(object_mesh.id_indices));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object_mesh.id_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float)*object_mesh.num_indices, object_mesh.indices, GL_STATIC_DRAW);

	//Normalss Buffer
	glGenBuffers(1, (GLuint*) &(object_mesh.id_normals));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object_mesh.id_normals);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float)*object_mesh.num_normals, object_mesh.normals, GL_STATIC_DRAW);

	//UVs Buffer
	glGenBuffers(1, (GLuint*) &(object_mesh.id_uvs));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object_mesh.id_uvs);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float)*object_mesh.num_uvs, object_mesh.uvs, GL_STATIC_DRAW);
}