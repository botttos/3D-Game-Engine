#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"

ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	App->camera->show_axis = true;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	//Delete GameObjects
	for (uint i = game_objects.size(); i > 0; i--)
	{
		delete[] game_objects[i];
	}
	return true;
}

GameObject * ModuleSceneIntro::CreateNewGameObject()
{
	GameObject* g_object = new GameObject();
	game_objects.push_back(g_object);
	return g_object;
}

// PreUpdate
update_status ModuleSceneIntro::PreUpdate(float dt)
{
	return(UPDATE_CONTINUE);
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	
	Plane p(0, 1, 0, 0);
	if (App->camera->show_grid == true)
	{
		if (App->camera->show_axis == true)
		{
			p.axis = true;
		}
		p.Render();
	}

	//Update Game Objects
	for (uint i = 0; i < game_objects.size(); i++)
	{
		game_objects[i]->Update();
	}
	
	if (go_window_enabled == true)
	{
		GameObjectWindow();
	}
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::GameObjectWindow()
{

}