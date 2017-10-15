#include "Application.h"
#include "ModuleFBX.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Devil/include/il.h"
#include "Devil/include/ilut.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")
#pragma comment (lib, "Devil/libx86/DevIL.lib")
#pragma comment ( lib, "Devil/libx86/ILU.lib" )
#pragma comment ( lib, "Devil/libx86/ILUT.lib" )

using namespace std;

ModuleFBX::ModuleFBX(bool start_enabled) : Module(start_enabled)
{}

ModuleFBX::~ModuleFBX()
{}

bool ModuleFBX::Start()
{
	bool ret = true;

	ilInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);

	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	return ret;
}

update_status ModuleFBX::Update(float dt)
{
	return UPDATE_CONTINUE;
}

uint ModuleFBX::GenerateTextureId(const char* texture_path)
{
	ILuint id;
	uint texture_id;
	ilGenImages(1, &id);
	ilBindImage(id);
	ilLoadImage(texture_path);

	texture_id = ilutGLBindTexImage();

	return texture_id;
}

bool ModuleFBX::CleanUp()
{
	aiDetachAllLogStreams();

	return true;
}

bool ModuleFBX::LoadFBX(const char* path)
{
	LOG("Loading the FBX...");
	this->path = path;
	std::string name(path);
	this->file_name = name.substr(name.find_last_of('\\') + 1);
	bool ret = true;
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		aiNode* rootNode = scene->mRootNode;

		for (int i = 0; i < rootNode->mNumChildren; ++i)
		{
			LoadModel(scene, rootNode->mChildren[i], path);
		}

		aiReleaseImport(scene);
		LOG("FBX loaded correctly --------------");
			return ret;
	}
	else
		LOG("ERROR, COULDN'T LOAD FBX ---------------");
		return false;
}

void ModuleFBX::LoadModel(const aiScene* scene, aiNode* node, const char* path)
{
	if (node->mNumMeshes <= 0)
	{
		LOG("Unable to load the mesh with path: %s. The number of meshes is below or equal to 0.", path);
	}
	else
	{
		LOG("Loading mesh from path %s", path);
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* new_mesh = scene->mMeshes[node->mMeshes[i]];
			mesh = ModelConfig();
			mesh.num_vertices = new_mesh->mNumVertices;
			mesh.vertices = new uint[mesh.num_vertices * 3];
			memcpy(mesh.vertices, new_mesh->mVertices, sizeof(float)*mesh.num_vertices * 3);

			glGenBuffers(1, (GLuint*)&(mesh.id_vertices));
			glBindBuffer(GL_ARRAY_BUFFER, mesh.id_vertices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * mesh.num_vertices, mesh.vertices, GL_STATIC_DRAW);

			if (new_mesh->HasFaces())
			{
				mesh.num_indices = new_mesh->mNumFaces * 3;
				mesh.indices = new uint[mesh.num_indices];
				for (uint j = 0; j < new_mesh->mNumFaces; j++)
				{
					if (new_mesh->mFaces[j].mNumIndices == 3)
					{
						memcpy(&mesh.indices[j * 3], new_mesh->mFaces[j].mIndices, 3 * sizeof(uint));
					}
				}

				glGenBuffers(1, (GLuint*)&(mesh.id_indices));
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.id_indices);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * mesh.num_indices, mesh.indices, GL_STATIC_DRAW);
			}
			else
			{
				LOG("Mesh with %i faces can not be loaded.", new_mesh->mNumFaces);
			}

			if (new_mesh->HasTextureCoords(mesh.id_uvs))
			{
				mesh.num_uvs = new_mesh->mNumVertices;
				mesh.uvs = new float[mesh.num_uvs * 2];

				for (int i = 0; i < new_mesh->mNumVertices; ++i)
				{
					memcpy(&mesh.uvs[i * 2], &new_mesh->mTextureCoords[0][i].x, sizeof(float));
					memcpy(&mesh.uvs[(i * 2) + 1], &new_mesh->mTextureCoords[0][i].y, sizeof(float));
				}

				glGenBuffers(1, (GLuint*)&(mesh.id_uvs));
				glBindBuffer(GL_ARRAY_BUFFER, mesh.id_uvs);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * mesh.num_uvs, mesh.uvs, GL_STATIC_DRAW);
			}
			else
			{ 
				LOG("Can't find texture coords for the specified mesh.");
			}

			if (new_mesh->HasNormals())
			{
				mesh.num_normals = new_mesh->mNumVertices;
				mesh.normals = new float[mesh.num_normals * 3];
				memcpy(mesh.normals, new_mesh->mNormals, sizeof(float) * mesh.num_normals * 3);

				glGenBuffers(1, (GLuint*)&(mesh.id_normals));
				glBindBuffer(GL_ARRAY_BUFFER, mesh.id_normals);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * mesh.num_normals, mesh.normals, GL_STATIC_DRAW);
			}
			else
			{
				LOG("Mesh has no normals.");
			}

			aiMaterial* material = scene->mMaterials[new_mesh->mMaterialIndex];

			if (material)
			{
				aiString path;
				material->GetTexture(aiTextureType_DIFFUSE, 0, &path);

				if (path.length > 0)
				{
					std::string base_path = "Textures/";
					std::string final_path = path.data;
					final_path.erase(0, final_path.find_last_of("\\") + 1);
					base_path += final_path;

					mesh.texture_id = GenerateTextureId(base_path.c_str());
					LOG("Texture with path %s has been loaded.", base_path.c_str());
					final_path.clear();
					base_path.clear();
				}
			}

			meshes.push_back(mesh);
			LOG("Loaded mesh with %i vertices.", mesh.num_vertices);
			LOG("Loaded mesh with %i indices.", mesh.num_indices);
			LOG("Loaded mesh with %i triangles.", mesh.num_vertices/3);
			LOG("Loaded mesh with %f normals.", mesh.num_normals);
			LOG("Loaded mesh with %f uvs.", mesh.num_uvs);
		}
	}

	for (int i = 0; i < node->mNumChildren; i++)
	{
		LoadModel(scene, node->mChildren[i], path);
	}

	mesh.position = (0.f, 0.f, 0.f);
	mesh.rotation = (0.f, 0.f, 0.f);
	mesh.scale = (1.f, 1.f, 1.f);

	LOG("Mesh position: (%f, %f, %f)", mesh.position.x, mesh.position.y, mesh.position.z);
	LOG("Mesh rotation: (%f, %f, %f)", mesh.rotation.x, mesh.rotation.y, mesh.rotation.z);
	LOG("Mesh scale: (%f, %f, %f)", mesh.scale.x, mesh.scale.y, mesh.scale.z);
}

void ModuleFBX::ApplyTexture(const char* path)
{
	ILuint id;
	ilGenImages(1, &id);
	ilBindImage(id);
	ilLoadImage(path);

	last_texture_id = ilutGLBindTexImage();
	LOG("Loaded and applied new texture correctly from path %s.", path);
}

uint ModuleFBX::GetTextureId()
{
	return(mesh.texture_id);
}

uint ModuleFBX::GetIndices()
{
	return(mesh.num_indices);
}

uint ModuleFBX::GetVertices()
{
	return(mesh.num_vertices);
}

float ModuleFBX::GetNormals()
{
	return(mesh.num_normals);
}

float ModuleFBX::GetUvs()
{
	return(mesh.num_uvs);
}

void ModuleFBX::GetFBXPosition(GLfloat &x, GLfloat &y, GLfloat &z)
{
	x = fbx_position[0];
	y = fbx_position[1];
	z = fbx_position[2];
}

vec3 ModuleFBX::GetPosition()
{
	return(mesh.position);
}

vec3 ModuleFBX::GetRotation()
{
	return(mesh.rotation);
}

vec3 ModuleFBX::GetScale()
{
	return(mesh.scale);
}