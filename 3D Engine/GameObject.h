#pragma once
#include "Globals.h"
#include "Component.h"
#include <string>
#include <vector>

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Update();

	void SetEnable();
	void SetDisable();
	bool IsActive();

	//Components
	void AddComponent(ComponentType type);
	Component* FindComponent(ComponentType type);
	
private:
	std::string name;

	std::vector<GameObject*> childs;
	GameObject* parent;
	bool active = true;

	//Components
	std::vector<Component*> components;
};