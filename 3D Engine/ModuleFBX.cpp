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

	ilutRenderer(ILUT_OPENGL);
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);

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
		App->renderer3D->DrawMeshes(meshes[i], GenerateTextureId("Baker_house.png"));
	}
	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
uint ModuleFBX::GenerateTextureId(const char* path)
{
	ILuint image_id;
	uint texture_id;

	ilGenImages(1, &image_id);
	ilBindImage(image_id);
	ilLoadImage(path);
	
	texture_id = ilutGLBindTexImage();

	ilDeleteImages(1, &image_id);
	LOG("TEXTURE CREATION SUCCESFUL ============================");

	return texture_id;
}

// LoadFBX ---------------------------------------------------------
bool ModuleFBX::LoadFBX(const char* path)
{
	bool ret = true;
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		aiNode* rootNode = scene->mRootNode;

		for (int i = 0; i < rootNode->mNumChildren; ++i)
			LoadModel(scene, rootNode->mChildren[i], path);

		aiReleaseImport(scene);
	}
	else
	{
		aiReleaseImport(scene);
		ret = false;
	}

	return ret;
}

// LoadModel -------------------------------------------------------
bool ModuleFBX::LoadModel(const aiScene* scene, aiNode* node, const char* file_name)
{
	bool ret = false;
	
	if (scene != nullptr && scene->HasMeshes())
	{
		//iterate all aiMesh structs
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			m = new GeometryBase(MESH);
			aiMesh* new_mesh = scene->mMeshes[node->mMeshes[i]];

			m->object_mesh.num_vertices = new_mesh->mNumVertices;
			m->object_mesh.vertices = new uint[m->object_mesh.num_vertices * 3];
			memcpy(m->object_mesh.vertices, new_mesh->mVertices, sizeof(float) * m->object_mesh.num_vertices * 3);
			
			glGenBuffers(1, (GLuint*)&(m->object_mesh.id_vertices));
			glBindBuffer(GL_ARRAY_BUFFER, m->object_mesh.id_vertices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * m->object_mesh.num_vertices, m->object_mesh.vertices, GL_STATIC_DRAW);

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

				glGenBuffers(1, (GLuint*)&(m->object_mesh.id_indices));
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->object_mesh.id_indices);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * m->object_mesh.num_indices, m->object_mesh.indices, GL_STATIC_DRAW);
			}

			if (new_mesh->HasTextureCoords(m->object_mesh.id_uvs))
			{
				m->object_mesh.num_uvs = new_mesh->mNumVertices;
				m->object_mesh.uvs = new float[m->object_mesh.num_uvs * 2];

				for (uint j = 0; j < new_mesh->mNumVertices; j++)
				{

					memcpy(&m->object_mesh.uvs[i * 2], &new_mesh->mTextureCoords[0][i].x, sizeof(float));
					memcpy(&m->object_mesh.uvs[(i * 2) + 1], &new_mesh->mTextureCoords[0][i].y, sizeof(float));
				}
				glGenBuffers(1, (GLuint*)&(m->object_mesh.id_uvs));
				glBindBuffer(GL_ARRAY_BUFFER, m->object_mesh.id_uvs);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * m->object_mesh.num_uvs, m->object_mesh.uvs, GL_STATIC_DRAW);
			}

			if (new_mesh->HasNormals())
			{
				m->object_mesh.num_normals = new_mesh->mNumVertices;
				m->object_mesh.normals = new float[m->object_mesh.num_normals * 3];
				memcpy(m->object_mesh.normals, new_mesh->mNormals, sizeof(float) * m->object_mesh.num_normals * 3);

				glGenBuffers(1, (GLuint*)&(m->object_mesh.id_normals));
				glBindBuffer(GL_ARRAY_BUFFER, m->object_mesh.id_normals);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * m->object_mesh.num_normals, m->object_mesh.normals, GL_STATIC_DRAW);
			}

			

			//Save space in VRAM and add the new mesh in the vector
			m->Start();
			meshes.push_back(m);
		}
		//aiReleaseImport(scene);
	}

	else
	{
		LOG("Error loading scene %s", file_name);
	}

	for (int i = 0; i < node->mNumChildren; i++)
	{
		LoadModel(scene, node->mChildren[i], file_name);
	}

	return ret;
}
