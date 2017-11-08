#pragma once
#include "GameObject.h"
#include "Application.h"
#include "ComponentTransform.h"
#include "ComponentMaterial.h"

GameObject::GameObject()
{
	AddComponent(C_TRANSFORM);
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	for (int i = 0; i < childs.size(); i++)
	{
		if (childs[i]->active == true)
		{
			childs[i]->Update();
		}
	}

	//Inspector window
	ImGui::Begin("Game Object Inspector");
	ImGui::SetWindowSize(ImVec2(500, 500), 0);
	// button code example (must be used to enable/disable component) 	if (ImGui::SmallButton("NAME")) component[i]->InvertState();
	
	//Iterate components vector Update
	for (int i = 0; i < components.size(); i++)
	{
		if (components.size() > 0)
		{
			if (components[i]->IsActive())
			{
				components[i]->Update();
			}
		}
		
	}
	ImGui::End();
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
	if (type == C_TRANSFORM)
	{
		LOG("add TRANSFORM COMPONENT");
		ComponentTransform* transform = new ComponentTransform(type);
		components.push_back(transform);
	}

	else if (type == C_MATERIAL)
	{
		LOG("add MATERIAL COMPONENT");
		ComponentMaterial* material = new ComponentMaterial(type);
		components.push_back(material);
		//Link to mesh(?
	}
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
