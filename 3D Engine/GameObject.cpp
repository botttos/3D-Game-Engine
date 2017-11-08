#pragma once
#include "GameObject.h"
#include "Application.h"

GameObject::GameObject()
{}

GameObject::~GameObject()
{}

void GameObject::Update()
{
	for (int i = 0; i < childs.size(); i++)
	{
		if (childs[i]->active == true)
		{
			childs[i]->Update();
		}
	}

	//Iterate components vector Update
	for (int i = 0; i < components.size(); i++)
	{
		if (App->scene_intro->go_inspector_enabled == true)
		{
			ImGui::Begin("Game Object Inspector");
			ImGui::SetWindowSize(ImVec2(500, 500), 0);
		}
		if (components[i]->IsActive() == true)
		{
			components[i]->Update();
		}
	}
	if (App->scene_intro->go_inspector_enabled == true)
	{
		ImGui::End();
	}
}

void GameObject::SetEnable()
{
	if (active == false)
	{
		active = true;
	}
}

void GameObject::SetDisable()
{
	if (active == true)
	{
		active = false;
	}
}

bool GameObject::IsActive()
{
	return active;
}

void GameObject::AddComponent(ComponentType type)
{
	Component* comp = new Component(type);
	components.push_back(comp);
}

Component * GameObject::FindComponent(ComponentType type)
{
	Component* desired_comp = nullptr;
	for (int i = 0; i < components.size(); i++)
	{
		if (components[i]->IsActive() == true && components[i]->type == type)
		{
			desired_comp = components[i];
			return desired_comp;
		}
	}

	return desired_comp;
}
