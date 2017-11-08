#include "ComponentTransform.h"
#include "Application.h"

ComponentTransform::ComponentTransform(ComponentType type) : Component(type)
{}

ComponentTransform::~ComponentTransform()
{}

void ComponentTransform::Update()
{
	if (App->scene_intro->go_inspector_enabled == true && this->IsActive() == true)
	{
		TransformInspector();
	}
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

void ComponentTransform::TransformInspector()
{
	if (ImGui::CollapsingHeader("Transform"), ImGuiTreeNodeFlags_DefaultOpen)
	{
		if (ImGui::SmallButton("Active")) InvertState();

		ImGui::Text("Position");
		ImGui::Text("[%f]   [%f]   [%f]", position[0], position[1], position[3]);

		ImGui::Text("Rotation");
		ImGui::Text("[%f]   [%f]   [%f]", rotation[0], rotation[1], rotation[2]);

		ImGui::Text("Scale");
		ImGui::Text("[%f]   [%f]   [%f]", scale[0], scale[1], scale[2]);
	}
}
