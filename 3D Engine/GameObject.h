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

	// Add component method
	// Add find component method
	bool active;
private:
	std::string name;

	std::vector<GameObject*> childs;
	GameObject* parent;
	// Add components vector(?
};