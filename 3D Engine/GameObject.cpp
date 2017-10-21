#pragma once
#include "GameObject.h"

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
