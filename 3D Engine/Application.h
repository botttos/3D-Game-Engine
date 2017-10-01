#pragma once

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleImGui.h"
#include "ModuleConsole.h"
#include "ModuleConfig.h"
#include "Globals.h"
#include "ModuleHardware.h"
#include "JSON\parson.h"
#include <list>
#include "ModulePrimitive.h"


class Console;
class Config;
class Hardware;
class ModulePrimitive;

using namespace std;

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleSceneIntro* scene_intro;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleImGui* imgui;
	Console* console;
	Config* config;
	Hardware* hardware;
	ModulePrimitive* primitive;

private:

	Timer	ms_timer;
	Timer   frame_time;

	float	dt;
	list<Module*> list_modules;
	
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();

public:
	JSON_Value * configuration;
};