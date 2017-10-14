#pragma once
#include "Module.h"
#include "Globals.h"
#include <vector>

class aiScene;
class aiNode;
class aiMaterial;

struct ModelConfig
{
	uint id_vertices = 0;
	uint num_indices = 0;
	uint* indices = nullptr;

	uint id_indices = 0;
	uint num_vertices = 0;
	uint* vertices = nullptr;

	uint id_normals = 0;
	uint num_normals = 0;
	float* normals = nullptr;

	uint id_uvs = 0;
	uint num_uvs = 0;
	float* uvs = nullptr;

	uint texture_id = 0;
};

class ModuleFBX : public Module
{
public:
	ModuleFBX(bool start_enabled = true);
	~ModuleFBX();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	bool LoadFBX(const char* path);
	void LoadModel(const aiScene* scene, aiNode* node, const char* path);
	void ApplyTexture(const char* path);
	uint GenerateTextureId(const char* texture_path);

	uint GetTextureId();

	vector<ModelConfig> meshes;

public:
	uint last_texture_id = 0;

private:
	ModelConfig data;
	ModelConfig mesh;
};