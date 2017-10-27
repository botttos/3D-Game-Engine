#include "SceneImporter.h"
#include "Globals.h"


// Scene importer ---------------------------------------------------------------------
void SceneImporter::SaveFile(ModelConfig mesh) const
{
	uint ranges[2] = { mesh.num_indices, mesh.num_vertices };
	uint size = sizeof(ranges) + (sizeof(uint) * mesh.num_indices) + (sizeof(float) * mesh.num_vertices * 3);

	char* data = new char[size];
	char* cursor = data;

	uint bytes = sizeof(ranges);
	memcpy(cursor, ranges, bytes);

	cursor += bytes;
	bytes = sizeof(uint) * mesh.num_indices;

	memcpy(cursor, mesh.indices, bytes);
}

void SceneImporter::LoadFile(char* buffer, ModelConfig* mesh) const
{
	char* cursor = buffer;

	uint ranges[5];
	uint bytes = sizeof(ranges);

	memcpy(ranges, cursor, bytes);

	mesh->num_indices = ranges[0];
	mesh->num_vertices = ranges[1];

	cursor += bytes;
	bytes = sizeof(uint) * mesh->num_indices;
	mesh->indices = new uint[mesh->num_indices];

	memcpy(mesh->indices, cursor, bytes);
}
// ------------------------------------------------------------------------------------