#pragma once
#include "MathGeoLib\MathGeoLib.h"
#include "Component.h"
#include <vector>

class GameObject;

class ComponentTransform :public Component
{
public:
	ComponentTransform(ComponentType type);
	~ComponentTransform();

	void Update();

	//Transform
	void SetPosition(float3 pos);
	void SetScale(float3 scale);
	void SetRotation(float3 rot);

	//Get private data
	float3 GetPosition() const;
	float3 GetScale() const;
	float3 GetRotation() const;
	float4x4 GetTransform() const;

private:
	float4x4 transform;

	//Axis
	float3 axis_x = { 1, 0, 0 };
	float3 axis_y = { 0, 1, 0 };
	float3 axis_z = { 0, 0, 1 };

	//-----------
	float3 position = { 0, 0, 0 };
	float3 scale = { 0, 0, 0 };
	float3 rotation = { 0, 0, 0 };

	//-----------
	void TransformInspector();
};