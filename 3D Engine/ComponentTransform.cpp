#include "ComponentTransform.h"

ComponentTransform::ComponentTransform(ComponentType type) : Component(type)
{}

ComponentTransform::~ComponentTransform()
{}

void ComponentTransform::Update()
{

}

void ComponentTransform::SetPosition(float3 pos)
{
	position = pos;
}

void ComponentTransform::SetScale(float3 scale)
{
	this->scale = scale;
}

void ComponentTransform::SetRotation(float3 rot)
{
	rotation = rot;
}

float3 ComponentTransform::GetPosition() const
{
	return position;
}

float3 ComponentTransform::GetScale() const
{
	return scale;
}

float3 ComponentTransform::GetRotation() const
{
	return rotation;
}

float4x4 ComponentTransform::GetTransform() const
{
	return transform;
}
