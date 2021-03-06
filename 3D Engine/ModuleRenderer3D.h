#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"

#define MAX_LIGHTS 8

struct ModelConfig;

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	update_status Update(float dt);
	bool CleanUp();
	bool DrawMeshes(const ModelConfig mesh) const;

	void OnResize(int width, int height);
	
public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
	bool enable_depth = false;
	bool enable_cull_face = false;
	bool enable_light = false;
	bool enable_color_material = false;
	bool enable_texture = false;
	bool enable_wireframe = false;
	bool enable_hardpoly = false;
};