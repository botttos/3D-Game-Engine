#include "ComponentMaterial.h"
#include "Application.h"

ComponentMaterial::ComponentMaterial(ComponentType type) : Component(type)
{}

ComponentMaterial::~ComponentMaterial()
{
}

void ComponentMaterial::Update()
{
	if (App->scene_intro->go_inspector_enabled == true && this->IsActive() == true)
	{
		ShowMaterialInspector();
	}
}

void ComponentMaterial::ShowMaterialInspector()
{
	if (ImGui::CollapsingHeader("Material"))
	{
		ImGui::Text("Showing only read information about the mesh material");
		ImGui::Separator();
		if (App->fbx_loader->last_texture_id == 0)
			ImGui::Image((ImTextureID)App->fbx_loader->GetTextureId(), ImVec2(200, 200));
		else
			ImGui::Image((ImTextureID)App->fbx_loader->last_texture_id, ImVec2(200, 200));
	}
}

void ComponentMaterial::SetTexture(std::vector<Texture> texture)
{
	this->texture = texture;
}

void ComponentMaterial::AddTexture(const Texture texture)
{
	this->texture.push_back(texture);
}
