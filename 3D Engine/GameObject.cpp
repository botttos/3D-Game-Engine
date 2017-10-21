#pragma once
#include "GameObject.h"

GameObject::GameObject()
{
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

	//Iterate components vector Update
}
