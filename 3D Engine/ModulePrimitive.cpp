#include "ModulePrimitive.h"
#include "Glew\include\glew.h"
#include "Application.h"
#include "SDL\include\SDL_opengl.h"
#include "gl\GL.h"
#include "gl\GLU.h"

#define BUFFER_OFFSET(i) ((void*)(i))

ModulePrimitive::ModulePrimitive(bool start_enabled) : Module(start_enabled)
{}

ModulePrimitive::~ModulePrimitive()
{
	LOG("Delete primitives");
	for (int i = spheres.size(); spheres.size() != 0; i--)
	{
		spheres.pop_back();
	}

	for (int i = cubes_indices.size(); cubes_indices.size() != 0; i--)
	{
		cubes_indices.pop_back();
	}

	for (int i = cylinders.size(); cylinders.size() != 0; i--)
	{
		cylinders.pop_back();
	}

	for (int i = normal_cubes.size(); normal_cubes.size() != 0; i--)
	{
		normal_cubes.pop_back();
	}
}	

bool ModulePrimitive::Start()
{
	return true;
}

bool ModulePrimitive::Update()
{
	for (int i = 0; i < spheres.size(); i++)
	{
		spheres[i]->UpdateSph();
	}

	for (int i = 0; i < cubes_indices.size(); i++)
	{
		cubes_indices[i]->UpdateCubeIndice();
	}

	for (int i = 0; i < cylinders.size(); i++)
	{
		cylinders[i]->UpdateCylinder();
	}
	for (int i = 0; i < normal_cubes.size(); i++)
	{
		normal_cubes[i]->UpdateNormalCube();
	}

	return UPDATE_CONTINUE;
}

bool ModulePrimitive::CleanUp()
{
	return false;
}

void ModulePrimitive::CreatePrimitive(GeomType primitive)
{
	if (primitive == CUBE)
	{
		NormalCubePrim* cube;
		cube = new NormalCubePrim();
		normal_cubes.push_back(cube);
	}
	else if (primitive == TRIANGLE)
	{
		LOG("Creating triangle");
		Triangle();
	}
	else if (primitive == CUBE_INDICE)
	{
		LOG("Creating cube with indices");
		CubeIndicePrim* cube_indice;
		cube_indice = new CubeIndicePrim();
		cubes_indices.push_back(cube_indice);
	}
	else if (primitive == SPHERE)
	{
		LOG("Creating sphere");
		SpherePrim* sphere;
		sphere = new SpherePrim(10, 10, 1);
		spheres.push_back(sphere);
	}
	else if (primitive == CYLINDER)
	{
		LOG("Creating cylinder")
		CylinderPrim* cylinder;
		cylinder = new CylinderPrim();
		cylinders.push_back(cylinder);
	}
	else if (primitive == ARROW)
	{

	}
	else if (primitive == AXIS)
	{

	}
	else if (primitive == RAY)
	{

	}
	else if (primitive == PLANE)
	{

	}
	else if (primitive == CAPSULE)
	{

	}
	else if (primitive == FRUSTUM)
	{

	}
}

void ModulePrimitive::Triangle()
{
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	// 
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// 1rst attribute buffer : vertex
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,
		3,                  // size
		GL_FLOAT,           // class
		GL_FALSE,           // normalized??
		0,
		(void*)0            // buffer gap
	);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}

// -------------------------------------------

SpherePrim::SpherePrim(int rings, int sectors, float radius) : rings(rings), sectors(sectors), radius(radius)
{
	float const R = 1. / (float)(rings - 1);
	float const S = 1. / (float)(sectors - 1);
	int r, s;

	sphere_vertices.resize(rings * sectors * 3);
	sphere_normals.resize(rings * sectors * 3);
	sphere_texcoords.resize(rings * sectors * 2);
	std::vector<GLfloat>::iterator v = sphere_vertices.begin();
	std::vector<GLfloat>::iterator n = sphere_normals.begin();
	std::vector<GLfloat>::iterator t = sphere_texcoords.begin();

	for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++)
	{
		float const y = sin(-M_PI_2 + M_PI * r * R);
		float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
		float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

		*t++ = s*S;
		*t++ = r*R;

		*v++ = x * radius;
		*v++ = y * radius;
		*v++ = z * radius;

		*n++ = x;
		*n++ = y;
		*n++ = z;
	}

	sphere_indices.resize(rings * sectors * 4);
	std::vector<GLushort>::iterator i = sphere_indices.begin();
	for (r = 0; r < rings - 1; r++) for (s = 0; s < sectors - 1; s++) {
		*i++ = r * sectors + s;
		*i++ = r * sectors + (s + 1);
		*i++ = (r + 1) * sectors + (s + 1);
		*i++ = (r + 1) * sectors + s;
	}
}

SpherePrim::~SpherePrim()
{
}

bool SpherePrim::UpdateSph()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, &sphere_vertices[0]);
	glNormalPointer(GL_FLOAT, 0, &sphere_normals[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &sphere_texcoords[0]);
	glDrawElements(GL_QUADS, sphere_indices.size(), GL_UNSIGNED_SHORT, &sphere_indices[0]);
	glPopMatrix();
	
	return true;
}

CubeIndicePrim::CubeIndicePrim()
{
	vertex =
	{
		0.5,0.5,0.5,// vertex 1
		-0.5,0.5,0.5,// vertex 2
		-0.5,-0.5,0.5, 
		0.5,-0.5,0.5,
		0.5,-0.5,-0.5,
		0.5,0.5,-0.5,
		-0.5,0.5,-0.5,
		-0.5,-0.5,0.5,
	};

	indices = 
	{ 
		0,1,2,  2,3,0, 
		0,3,4,  4,5,0,  
		0,5,6,  6,1,0,  
		1,6,7,  7,2,1,  
		7,4,3,  3,2,7,  
		4,7,6,  6,5,4 
	};

	glGenBuffers(1, &vertices_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), &vertex[0], GL_STATIC_DRAW);

	glGenBuffers(1, &indices_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);
}

CubeIndicePrim::~CubeIndicePrim()
{
}

bool CubeIndicePrim::UpdateCubeIndice()
{
	glEnableClientState(GL_ARRAY_BUFFER);
	glEnableClientState(GL_ELEMENT_ARRAY_BUFFER);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_id);
	

	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glDrawElements(
		GL_TRIANGLES,   //- mode
		vertex.size()/3,//- count
		GL_UNSIGNED_INT,//- type
		NULL			//- element array buffer offset
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableClientState(GL_ARRAY_BUFFER);
	glDisableClientState(GL_ELEMENT_ARRAY_BUFFER);

	return true;
}

CylinderPrim::CylinderPrim()
{}

CylinderPrim::~CylinderPrim()
{
}

bool CylinderPrim::UpdateCylinder()
{
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat angle = 0.0;
	GLfloat angle_stepsize = 0.1;

	/** Draw the tube */
	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	while (angle < 2 * 3.14f) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		glVertex3f(x, y, 0.0);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glVertex3f(radius, 0.0, 0.0);
	glEnd();

	/** Draw the circle on top of cylinder */
	glBegin(GL_POLYGON);
	angle = 0.0;
	while (angle < 2 * 3.14f) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		angle = angle + angle_stepsize;
	}

	glVertex3f(radius, 0.0, height);
	glEnd();
	return true;
}


NormalCubePrim::NormalCubePrim()
{
	vertex = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f, 
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

}

NormalCubePrim::~NormalCubePrim()
{}

bool NormalCubePrim::UpdateNormalCube()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &vertex[0]);
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

	glDisableVertexAttribArray(0);

	glDisableClientState(0);

	return true;
}


