#include "ModuleFBX.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

ModuleFBX::ModuleFBX(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

ModuleFBX::~ModuleFBX()
{}

// -----------------------------------------------------------------
bool ModuleFBX::Start()
{
	bool ret = true;
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	return ret;
}

// -----------------------------------------------------------------
bool ModuleFBX::CleanUp()
{
	aiDetachAllLogStreams();

	return true;
}

// -----------------------------------------------------------------
update_status ModuleFBX::Update(float dt)
{

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleFBX::LoadFBX(const char* file_name)
{
	const aiScene* scene = aiImportFile(file_name, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		for (int i = 0; i <= scene->mNumMeshes; ++i)
		{
			//I don't really know what to do here, I know that we have to use scene->nMeshes[i] somewhere (?).
			//As said on the pdf: "Use scene->mNumMeshes to iterate on scene->mMeshes array, but I don't know what to do here yet.
		}
		aiReleaseImport(scene);
	}
	else
		LOG("Error loading scene %s", file_name);

	aiMesh* new_mesh;
	ModelConfig model;
	
	model.num_vertices = new_mesh->mNumVertices;
	model.vertices = new float[model.num_vertices * 3];
	memcpy(model.vertices, new_mesh->mVertices, sizeof(float) * model.num_vertices * 3);
	LOG("New mesh with %d vertices", model.num_vertices);

	if (new_mesh->HasFaces())
	{
		model.num_indices = new_mesh->mNumFaces * 3;
		model.indices = new uint[model.num_indices];

		for (uint i = 0; i < new_mesh->mNumFaces; ++i)
		{
			if (new_mesh->mFaces[i].mNumIndices != 3)
			{
				LOG("WARNING, geometry face with != 3 inidces!");
			}
			else
			{
				memcpy(&model.indices[i * 3], new_mesh->mFaces[i].mIndices, 3 * sizeof(uint));
			}
		}
	}


}
