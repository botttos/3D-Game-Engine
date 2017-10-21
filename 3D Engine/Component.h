#pragma once

enum ComponentType
{
	C_TRANSFORM = 0,
	C_MESH,
	C_MATERIAL
};

class Component
{
public:
	Component(ComponentType type);
	~Component();

	void Update();
	void Enable();
	void Disable();

	ComponentType type;

private:
	bool active;
};