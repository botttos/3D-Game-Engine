#include "Component.h"

Component::Component(ComponentType type) : type(type)
{}

Component::~Component()
{}

void Component::Update()
{}

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
