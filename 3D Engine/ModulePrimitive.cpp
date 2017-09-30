#include "ModulePrimitive.h"
#include "Glew\include\glew.h"
#include "Application.h"
#include "ModuleImGui.h"
#include "imGUI\imgui.h"
#include "imGUI\imgui_impl_sdl_gl3.h"
#include "MathGeoLib\MathGeoLib.h"
#include "ModuleConsole.h"
#include "SDL\include\SDL_opengl.h"
#include "gl\GL.h"
#include "gl\GLU.h"

#define BUFFER_OFFSET(i) ((void*)(i))

ModulePrimitive::ModulePrimitive(Application * app, bool start_enabled) : Module(app, start_enabled)
{}

ModulePrimitive::~ModulePrimitive()
{}

bool ModulePrimitive::Start()
{

	return true;
}

bool ModulePrimitive::Update()
{
	if (this->type == CUBE)
	{
		CreateCube();
	}
	else if (this->type == TRIANGLE)
	{
		CreateTriangle();
	}
	else if (this->type == CUBE_INDICE)
	{
		CreateCubeIndice();
	}

	return UPDATE_CONTINUE;
}

bool ModulePrimitive::CleanUp()
{
	return false;
}

bool ModulePrimitive::SetType(int type)
{
	if (type != this->type)
	{
		this->type = type;
	}
	else
		this->type = EMPTY;

	return true;
}

void ModulePrimitive::CreateTriangle()
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

void ModulePrimitive::CreateCube()
{
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	static const GLfloat g_vertex_buffer_data[] = {
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

	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	glDisableVertexAttribArray(0);
}

void ModulePrimitive::CreateCubeIndice()
{
	GLfloat vertices2[] = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,   1,-1, 1,   // v0,v1,v2,v3 (front)
		1, 1, 1,   1,-1, 1,   1,-1,-1,   1, 1,-1,   // v0,v3,v4,v5 (right)
		1, 1, 1,   1, 1,-1,  -1, 1,-1,  -1, 1, 1,   // v0,v5,v6,v1 (top)
		-1, 1, 1,  -1, 1,-1,  -1,-1,-1,  -1,-1, 1,   // v1,v6,v7,v2 (left)
		-1,-1,-1,   1,-1,-1,   1,-1, 1,  -1,-1, 1,   // v7,v4,v3,v2 (bottom)
		1,-1,-1,  -1,-1,-1,  -1, 1,-1,   1, 1,-1 }; // v4,v7,v6,v5 (back)

	GLubyte indices[] = { 0, 1, 2,   2, 3, 0,      // front
		4, 5, 6,   6, 7, 4,      // right
		8, 9,10,  10,11, 8,      // top
		12,13,14,  14,15,12,      // left
		16,17,18,  18,19,16,      // bottom
		20,21,22,  22,23,20 };    // back

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices2);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);


	glDisableClientState(0);  // disable vertex arrays

}

