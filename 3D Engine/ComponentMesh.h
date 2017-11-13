#pragma once
#include "Component.h"

class ComponentMesh : public Component
{
public:
	ComponentMesh(ComponentType type);
	~ComponentMesh();

	void Update();
	void ShowMeshInspector();

private:

	
};