#include "ModuleFBX.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"
#include "Devil/include/il.h"
#include "Devil/include/ilut.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")
#pragma comment (lib, "Devil/libx86/DevIL.lib")
#pragma comment ( lib, "Devil/libx86/ILU.lib" )
#pragma comment ( lib, "Devil/libx86/ILUT.lib" )

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
	for (uint i = 0; i < meshes.size(); i++)
	{
		meshes[i]->Draw();
	}
	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
bool ModuleFBX::LoadFBX(const char* file_name)
{
	bool ret = false;
	aiMesh* new_mesh = nullptr;
	const aiScene* scene = aiImportFile(file_name, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		//iterate all aiMesh structs
		for (uint i = 0; i < scene->mNumMeshes; i++)
		{
			m = new GeometryBase(MESH);
			new_mesh = scene->mMeshes[i];

			m->object_mesh.num_vertices = new_mesh->mNumVertices;
			m->object_mesh.vertices = new float[m->object_mesh.num_vertices * 3];
			memcpy(m->object_mesh.vertices, new_mesh->mVertices, sizeof(float) * m->object_mesh.num_vertices * 3);

			LOG("New mesh with %d vertices", m->object_mesh.num_vertices);

			if (new_mesh->HasFaces())
			{
				m->object_mesh.num_indices = new_mesh->mNumFaces * 3;
				m->object_mesh.indices = new uint[m->object_mesh.num_indices]; //Each face is a triangle

				for (uint j = 0; j < new_mesh->mNumFaces; j++)
				{
					if (new_mesh->mFaces[j].mNumIndices != 3)
					{
						LOG("WARNING, geometry face with != 3 indices!");
					}
					else
					{
						memcpy(&m->object_mesh.indices[j * 3], new_mesh->mFaces[j].mIndices, 3 * sizeof(uint));
					}
				}

				//Save space in VRAM and add the new mesh in the vector
				m->Start();
				meshes.push_back(m);
			}
		}
		aiReleaseImport(scene);
	}

	else
	{
		LOG("Error loading scene %s", file_name);
	}

	return ret;
}
