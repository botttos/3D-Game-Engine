#pragma once
#include "Component.h"
#include <string>
#include <vector>

struct Texture
{
	uint id;
	std::string type;
	std::string path;
};

class ComponentMaterial : public Component
{
public:
	ComponentMaterial(ComponentType type);
	~ComponentMaterial();

	void Update();
	void ShowMaterialInspector();
	void SetTexture(std::vector<Texture> texture);
	void AddTexture(const Texture texture);

private:

	std::vector<Texture> texture;
};