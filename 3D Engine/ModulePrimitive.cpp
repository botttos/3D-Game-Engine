#include "ModulePrimitive.h"
#include "Glew\include\glew.h"
#include "Application.h"
#include "SDL\include\SDL_opengl.h"
#include "gl\GL.h"
#include "gl\GLU.h"
#include "Devil/include/il.h"
#include "Devil/include/ilut.h"

#pragma comment (lib, "Devil/libx86/DevIL.lib")
#pragma comment ( lib, "Devil/libx86/ILU.lib" )
#pragma comment ( lib, "Devil/libx86/ILUT.lib" )

#define BUFFER_OFFSET(i) ((void*)(i))

ModulePrimitive::ModulePrimitive(Application * app, bool start_enabled) : Module(app, start_enabled)
{}

ModulePrimitive::~ModulePrimitive()
{}

bool ModulePrimitive::Start()
{

	// - Sphere
	unsigned int rings = 10;
	unsigned int sectors = 10;
	float radius = 1;

	float const R = 1. / (float)(rings - 1);
	float const S = 1. / (float)(sectors - 1);
	int r, s;

	ilInit();
	iluInit();
	ilutInit();

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

	// Checkered texture creation
	GLubyte checkered_texture[64][64][4];
	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkered_texture[i][j][0] = (GLubyte)c;
			checkered_texture[i][j][1] = (GLubyte)c;
			checkered_texture[i][j][2] = (GLubyte)c;
			checkered_texture[i][j][3] = (GLubyte)255;
		}
	}

	// Generate and bind a texture buffer
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, NULL);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64,
		0, GL_RGBA, GL_UNSIGNED_BYTE, checkered_texture);

	return true;
}

bool ModulePrimitive::Update()
{
	if (this->type == CUBE)
	{
		CubeVertex();
	}
	else if (this->type == TRIANGLE)
	{
		Triangle();
	}
	else if (this->type == CUBE_INDICE)
	{
		CubeIndice();
	}
	else if (this->type == CUBE_TEXTURIZED)
	{
		CubeDirect();
	}
	else if (this->type == SPHERE)
	{
		Sphere();
	}
	else if (this->type == CYLINDER)
	{
		Cylinder();
	}
	else if (this->type == ARROW)
	{
		
	}
	else if (this->type == AXIS)
	{
		
	}
	else if (this->type == RAY)
	{
		
	}
	else if (this->type == PLANE)
	{
		
	}
	else if (this->type == CAPSULE)
	{
		
	}
	else if (this->type == FRUSTUM)
	{
		
	}

	return UPDATE_CONTINUE;
}

bool ModulePrimitive::CleanUp()
{
	return false;
}

bool ModulePrimitive::SetType(GeomType type)
{
	if (type != this->type)
	{
		this->type = type;
	}
	else
		this->type = EMPTY;

	return true;
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

void ModulePrimitive::CubeVertex()
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


}

void ModulePrimitive::CubeIndice()
{
	static const GLfloat vertices2[] = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,   1,-1, 1,   // v0,v1,v2,v3 (front)
		1, 1, 1,   1,-1, 1,   1,-1,-1,   1, 1,-1,   // v0,v3,v4,v5 (right)
		1, 1, 1,   1, 1,-1,  -1, 1,-1,  -1, 1, 1,   // v0,v5,v6,v1 (top)
		-1, 1, 1,  -1, 1,-1,  -1,-1,-1,  -1,-1, 1,   // v1,v6,v7,v2 (left)
		-1,-1,-1,   1,-1,-1,   1,-1, 1,  -1,-1, 1,   // v7,v4,v3,v2 (bottom)
		1,-1,-1,  -1,-1,-1,  -1, 1,-1,   1, 1,-1 }; // v4,v7,v6,v5 (back)

	static const GLubyte indices[] = { 0, 1, 2,   2, 3, 0,      // front
		4, 5, 6,   6, 7, 4,      // right
		8, 9,10,  10,11, 8,      // top
		12,13,14,  14,15,12,      // left
		16,17,18,  18,19,16,      // bottom
		20,21,22,  22,23,20 };    // back
	
	

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices2);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

	glDisableVertexAttribArray(0);

	glDisableClientState(0);  // disable vertex arrays
}

void ModulePrimitive::CubeDirect()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBegin(GL_TRIANGLES);
	
	// Front -----------------------
	glTexCoord2d(0.f, 0.f); 
	glVertex3f(0.f, 0.f, 1.f);
	glTexCoord2d(0.f, 1.f);
	glVertex3f(1.f, 0.f, 1.f);
	glTexCoord2d(1.f, 1.f);
	glVertex3f(1.f, 1.f, 1.f);
	
	glTexCoord2d(0.f, 0.f);
	glVertex3f(0.f, 0.f, 1.f);
	glTexCoord2d(1.f, 1.f);
	glVertex3f(1.f, 1.f, 1.f);
	glTexCoord2d(1.f, 0.f);
	glVertex3f(0.f, 1.f, 1.f);
	
	//Right ------------------------
	glTexCoord2d(0.f, 0.f);
	glVertex3f(1.f, 0.f, 1.f); 
	glTexCoord2d(0.f, 1.f);
	glVertex3f(1.f, 0.f, 0.f);
	glTexCoord2d(1.f, 0.f);
	glVertex3f(1.f, 1.f, 1.f);
	
	glTexCoord2d(0.f, 1.f);
	glVertex3f(1.f, 0.f, 0.f);
	glTexCoord2d(1.f, 1.f);
	glVertex3f(1.f, 1.f, 0.f);
	glTexCoord2d(1.f, 0.f);
	glVertex3f(1.f, 1.f, 1.f);
	
	//Left -------------------------
	glTexCoord2d(0.f, 0.f);
	glVertex3f(0.f, 0.f, 0.f); 
	glTexCoord2d(0.f, 1.f);
	glVertex3f(0.f, 0.f, 1.f);
	glTexCoord2d(1.f, 0.f);
	glVertex3f(0.f, 1.f, 0.f);
	
	glTexCoord2d(0.f, 1.f);
	glVertex3f(0.f, 0.f, 1.f);
	glTexCoord2d(1.f, 1.f);
	glVertex3f(0.f, 1.f, 1.f);
	glTexCoord2d(1.f, 0.f);
	glVertex3f(0.f, 1.f, 0.f);
	
	//Back -------------------------
	glTexCoord2d(0.f, 0.f);
	glVertex3f(1.f, 0.f, 0.f); 
	glTexCoord2d(1.f, 1.f);
	glVertex3f(0.f, 1.f, 0.f);
	glTexCoord2d(1.f, 0.f);
	glVertex3f(1.f, 1.f, 0.f);
	
	glTexCoord2d(0.f, 1.f);
	glVertex3f(0.f, 0.f, 0.f);
	glTexCoord2d(1.f, 1.f);
	glVertex3f(0.f, 1.f, 0.f);
	glTexCoord2d(0.f, 0.f);
	glVertex3f(1.f, 0.f, 0.f);
	
	//Up ---------------------------
	glTexCoord2d(0.f, 1.f);
	glVertex3f(1.f, 1.f, 1.f); 
	glTexCoord2d(0.f, 0.f);
	glVertex3f(1.f, 1.f, 0.f);
	glTexCoord2d(1.f, 0.f);
	glVertex3f(0.f, 1.f, 0.f);
	
	glTexCoord2d(0.f, 1.f);
	glVertex3f(1.f, 1.f, 1.f);
	glTexCoord2d(1.f, 0.f);
	glVertex3f(0.f, 1.f, 0.f);
	glTexCoord2d(1.f, 1.f);
	glVertex3f(0.f, 1.f, 1.f);
	
	//Bottom -----------------------
	glTexCoord2d(1.f, 1.f);
	glVertex3f(1.f, 0.f, 1.f); 
	glTexCoord2d(0.f, 1.f);
	glVertex3f(0.f, 0.f, 1.f);
	glTexCoord2d(0.f, 0.f);
	glVertex3f(0.f, 0.f, 0.f);
	
	glTexCoord2d(1.f, 1.f);
	glVertex3f(1.f, 0.f, 1.f);
	glTexCoord2d(0.f, 0.f);
	glVertex3f(0.f, 0.f, 0.f);
	glTexCoord2d(1.f, 0.f);
	glVertex3f(1.f, 0.f, 0.f);
	
	glEnd();
}

void ModulePrimitive::Sphere()
{

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, &sphere_vertices[0]);
	glNormalPointer(GL_FLOAT, 0, &sphere_normals[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &sphere_texcoords[0]);
	glDrawElements(GL_QUADS, sphere_indices.size(), GL_UNSIGNED_SHORT, &sphere_indices[0]);
	glPopMatrix();

}

void ModulePrimitive::Cylinder()
{
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat angle = 0.0;
	GLfloat angle_stepsize = 0.1;

	float radius = 1.0f;
	float height = 3.0f;

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
}

