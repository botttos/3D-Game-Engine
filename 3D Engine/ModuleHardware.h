#ifndef _MODULE_HARDWARE_H_
#define _MODULE_HARDWARE_H_

#include "Module.h"
#include "Glew\include\glew.h"
#include "SDL/include/SDL_cpuinfo.h"
#include "SDL/include/SDL_opengl.h"

class Hardware : public Module
{
public:

	Hardware(Application* app, bool start_enabled = false);
	~Hardware() {};

	bool Start();
	update_status Update(float dt);
	void Draw();

private:

	const GLubyte* vendor = nullptr;
	const GLubyte* gpu_name = nullptr;
	const GLubyte* version = nullptr;

	GLint memory_usage = 0;
	GLint dedicated_memory = 0;
	GLint total_memory = 0;
	GLint available_memory = 0;
	
	//------
	
	int cpus = 0;
	int cache = 0;
	int system_ram = 0;

	bool avx = false;
	bool rdtsc = false;
	bool mmx = false;
	bool sse = false;
	bool sse2 = false;
	bool sse3 = false;
	bool sse41 = false;
	bool sse42 = false;
	
};


#endif // !_MODULE_HARDWARE_H_


