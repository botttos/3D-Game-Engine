#pragma once
#include "GameObject.h"

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
	virtual ~Component();

	virtual void Update();
	virtual void Enable();
	virtual void Disable();

	bool IsActive() const;
	bool InvertState();
	void SetActive();
	void SetDisable();
	ComponentType type;

private:
	bool active = true;
};