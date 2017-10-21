#pragma once
#include <string>
#include "Globals.h"
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
	// Add component method
	// Add find component method
	
private:
	std::string name;

	std::vector<GameObject*> childs;
	GameObject* parent;
	bool active = true;
	// Add components vector(?
};