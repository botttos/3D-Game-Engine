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

}

bool GeometryBase::Draw()
{
	bool ret = false;

	if (object_mesh.num_vertices > 0 && object_mesh.num_indices > 0)
	{
		glEnableClientState(GL_VERTEX_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, object_mesh.id_vertices);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object_mesh.id_indices);

		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glDrawElements(GL_TRIANGLES, object_mesh.num_indices, GL_UNSIGNED_INT, NULL);

		glDisableClientState(GL_VERTEX_ARRAY);
		
		ret = true;
	}

	else
	{
		LOG("Fail drawing mesh");
	}

	return ret;
}