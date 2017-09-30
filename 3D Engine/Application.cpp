#include "Application.h"
#include "ModuleConfig.h"
#include "Brofiler\include\Brofiler.h"
#include "Globals.h"


Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this, true);
	scene_intro = new ModuleSceneIntro(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	//physics = new ModulePhysics3D(this);
	player = new ModulePlayer(this);
	primitive = new ModulePrimitive(this);
	imgui = new ModuleImGui(this);
	//Console
	console = new Console(this);
	config = new Config(this);
	//Hardware
	hardware = new Hardware(this);
	
	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	AddModule(audio);
	//AddModule(physics);
	

	// Scenes
	AddModule(scene_intro);
	AddModule(player);
	AddModule(primitive);
	AddModule(imgui);

	//Console
	AddModule(console);
	AddModule(config);
	AddModule(hardware);
	// Renderer last!
	AddModule(renderer3D);
	
}

Application::~Application()
{
	list<Module*>::iterator item = list_modules.begin();

	while(item != list_modules.end())
	{
		delete (item._Ptr->_Myval);
		item++;
	}
}

bool Application::Init()
{
	bool ret = true;

	// JSON data from config
	void json_set_allocation_functions(JSON_Malloc_Function malloc_fun, JSON_Free_Function free_fun);
	configuration = json_parse_file("config.json");

	if (configuration == NULL)
	{
		LOG("=================================== Specified file could not load");
		ret = false;
	}
	else
	{
		LOG("=================================== COnfiguration file opened without any problem");
	}
	
	// Call Init() in all modules
	list<Module*>::iterator item = list_modules.begin();

	while(item != list_modules.end() && ret == true)
	{
		ret = item._Ptr->_Myval->Init();
		item++;
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	item = list_modules.begin();

	while(item != list_modules.end() && ret == true)
	{
		ret = item._Ptr->_Myval->Start();
		item++;
	}
	
	ms_timer.Start();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();
	frame_time.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
	uint32 last_frame_ms = frame_time.Read();
	if(config->GetFPS() > 0 && last_frame_ms < config->GetFPS())
	{
		float cap_fps = 1000 / (float)config->GetFPS();
		SDL_Delay(cap_fps - last_frame_ms);
	}
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	list<Module*>::iterator item = list_modules.begin();
	
	while(item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = item._Ptr->_Myval->PreUpdate(dt);
		item++;
	}

	item = list_modules.begin();

	while(item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = item._Ptr->_Myval->Update(dt);
		item++;
	}

	item = list_modules.begin();

	while(item != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		ret = item._Ptr->_Myval->PostUpdate(dt);
		item++;
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	list<Module*>::iterator item = list_modules.begin();

	while(item != list_modules.end() && ret == true)
	{
		ret = item._Ptr->_Myval->CleanUp();
		item++;
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}