#include "Component.h"

Component::Component(ComponentType type) : type(type)
{}

Component::~Component()
{}

void Component::Update()
{
}

void Component::Enable()
{
	if (active == false)
	{
		active = true;
	}
}

void Component::Disable()
{
	if (active == true)
	{
		active = false;
	}
}

bool Component::IsActive() const
{
	return active;
}

bool Component::InvertState()
{
	if(active == true)
	{
		active = false;
	}
	else
	{
		active = true;
	}

	return active;
}

void Component::SetActive()
{
	active = true;
}

void Component::SetDisable()
{
	active = false;
}
