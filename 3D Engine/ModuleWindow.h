#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init();
	bool CleanUp();

	void SetTitle(const char* title);

	void SetFullScreen(bool fullscreen);
	void SetWindowed(bool borderless);
	void SetWindowBrigthness(float brigthness);
	void SetWindowWidth(int w);
	void SetWindowHeight(int h);
	void SetWindowFullDesktop();

public:
	//The window we'll be rendering to
	SDL_Window* window;
	bool fullscreen = false;
	bool windowed = false;
	bool full_desktop = false;
	//The surface contained by the window
	SDL_Surface* screen_surface;
};

#endif // __ModuleWindow_H__