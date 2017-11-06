#pragma once
#include "Module.h"
#include "Globals.h"
#include "Primitive.h"
#include "GameObject.h"
#include <vector>

#define MAX_SNAKE 2

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	update_status PreUpdate(float dt);
	bool CleanUp();
	void GameObjectWindow();

	//Game Object Creation
	GameObject* CreateNewGameObject();
	bool go_window_enabled = true;

private:
	std::vector<GameObject*> game_objects;
};
