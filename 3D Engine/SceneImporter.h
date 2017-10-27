#pragma once
#include "ModuleFBX.h"


class SceneImporter
{
	void SaveFile(ModelConfig mesh) const;
	void LoadFile(char* buffer, ModelConfig* mesh) const;
};
