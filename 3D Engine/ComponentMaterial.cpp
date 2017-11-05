#include "ComponentMaterial.h"

ComponentMaterial::ComponentMaterial(ComponentType type) : Component(type)
{}

ComponentMaterial::~ComponentMaterial()
{
}

void ComponentMaterial::SetTexture(std::vector<Texture> texture)
{
	this->texture = texture;
}

void ComponentMaterial::AddTexture(const Texture texture)
{
	this->texture.push_back(texture);
}
