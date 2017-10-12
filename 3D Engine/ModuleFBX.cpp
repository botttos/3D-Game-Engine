#include "ModuleFBX.h"
#include "Application.h"
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

ModuleFBX::ModuleFBX(bool start_enabled) : Module(start_enabled)
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

	ilInit();
	iluInit();
	ilutInit();
	
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
		App->renderer3D->DrawMeshes(meshes[i]);
	}
	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
uint ModuleFBX::GenerateTextureId(const char* path)
{
	ILuint image_id;
	uint texture_id;
	ILboolean success;
	ILenum error;

	ilGenImages(1, &image_id);
	ilBindImage(image_id);

	success = ilLoadImage(path);

	if (success)
	{
		ILinfo image_info;
		iluGetImageInfo(&image_info);
		if (image_info.Origin == IL_ORIGIN_UPPER_LEFT)
			iluFlipImage();

		success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);

		if (!success)
		{
			error = ilGetError();
			LOG("IMAGE CONVERSION FAILED! ===========================");
			LOG("Error: %s", error);
			LOG("%s", iluErrorString(error));
			exit(-1);
		}

		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D,
			0,
			ilGetInteger(IL_IMAGE_FORMAT),
			ilGetInteger(IL_IMAGE_WIDTH),
			ilGetInteger(IL_IMAGE_HEIGHT),
			0,
			ilGetInteger(IL_IMAGE_FORMAT),
			GL_UNSIGNED_BYTE,
			ilGetData());
	}
	else
	{
		error = ilGetError();
		LOG("IMAGE LOADING FAILED! ===========================");
		LOG("Error: %s", error);
		LOG("%s", iluErrorString(error));
		exit(-1);
	}

	ilDeleteImages(1, &image_id);
	LOG("TEXTURE CREATION SUCCESFUL ============================");

	return texture_id;
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
			}

			if (new_mesh->HasNormals())
			{
				m->object_mesh.num_normals = new_mesh->mNumVertices;
				m->object_mesh.normals = new float[m->object_mesh.num_normals * 3];
				memcpy(m->object_mesh.normals, new_mesh->mNormals, sizeof(float) * m->object_mesh.num_normals * 3);
			}

			if (new_mesh->HasTextureCoords(m->object_mesh.id_uvs))
			{
				m->object_mesh.num_uvs = new_mesh->mNumVertices;
				m->object_mesh.uvs = new float[m->object_mesh.num_uvs * 2];

				for (uint j = 0; j < new_mesh->mNumVertices; j++)
				{
					if (new_mesh->mNumVertices == 0)
					{
						LOG("WARNING, geometry with 0 vertices!");
					}
					else
					{
						memcpy(&m->object_mesh.uvs[i * 2], &new_mesh->mTextureCoords[0][i].x, sizeof(float));
						memcpy(&m->object_mesh.uvs[(i * 2) + 1], &new_mesh->mTextureCoords[0][i].y, sizeof(float));
					}
				}
			}

			//Save space in VRAM and add the new mesh in the vector
			m->Start();
			meshes.push_back(m);

		}
		aiReleaseImport(scene);
	}

	else
	{
		LOG("Error loading scene %s", file_name);
	}

	return ret;
}
