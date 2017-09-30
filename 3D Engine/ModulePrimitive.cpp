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

	return UPDATE_CONTINUE;
}

bool ModulePrimitive::CleanUp()
{
	return false;
}

bool ModulePrimitive::SetType(int type)
{
	this->type = type;

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

