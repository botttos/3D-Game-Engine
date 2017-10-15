#pragma once
#include "Module.h"
#include "Globals.h"
#include <string>

#define MAX_MOUSE_BUTTONS 5

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

enum FILE_TYPE
{
	GEOMETRY_MODEL=0,
	TEXTURE,
	UNKNOWN,
	DIR_NULLPTR
};

class ModuleInput : public Module
{
public:
	
	ModuleInput(bool start_enabled = true);
	~ModuleInput();

	bool Init();
	update_status PreUpdate(float dt);
	bool CleanUp();

	const KEY_STATE GetKey(const int id) const
	{
		return keyboard[id];
	}

	const KEY_STATE GetMouseButton(const int id) const
	{
		return mouse_buttons[id];
	}

	int GetMouseX() const
	{
		return mouse_x;
	}

	int GetMouseY() const
	{
		return mouse_y;
	}

	int GetMouseZ() const
	{
		return mouse_z;
	}

	int GetMouseXMotion() const
	{
		return mouse_x_motion;
	}

	int GetMouseYMotion() const
	{
		return mouse_y_motion;
	}

	const FILE_TYPE GetFileType(const char* dir) const;

	bool Quit();
	
private:
	KEY_STATE* keyboard;
	KEY_STATE mouse_buttons[MAX_MOUSE_BUTTONS];
	int mouse_x;
	int mouse_y;
	int mouse_z;
	int mouse_x_motion;
	int mouse_y_motion;
	bool quit_app = false;

	std::string file_path;
};