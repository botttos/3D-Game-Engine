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
