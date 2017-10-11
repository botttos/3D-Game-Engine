#include "ModuleHardware.h"
#include "Glew\include\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "imGUI\imgui.h"
#include "imGUI\imgui_impl_sdl_gl3.h"

/* Video Memory */
#define GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX			0x9047
#define GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX		0x9048
#define GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX    0x9049
#define GPU_MEMORY_INFO_EVICTION_COUNT_NVX				0x904A
#define GPU_MEMORY_INFO_EVICTED_MEMORY_NVX				0x904B

Hardware::Hardware(bool start_enabled) : Module(start_enabled)
{
}

bool Hardware::Start()
{
	
	avx = SDL_HasAVX();
	rdtsc = SDL_HasRDTSC();
	mmx = SDL_HasMMX();
	sse = SDL_HasSSE();
	sse2 = SDL_HasSSE2();
	sse3 = SDL_HasSSE3();
	sse41 = SDL_HasSSE41();
	sse42 = SDL_HasSSE42();
	
	cpus = SDL_GetCPUCount();
	cache = SDL_GetCPUCacheLineSize();
	system_ram = SDL_GetSystemRAM();

	vendor = glGetString(GL_VENDOR);
	gpu_name = glGetString(GL_RENDERER);
	version = glGetString(GL_VERSION);
	glGetIntegerv(GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &total_memory);

	return true;
}

update_status Hardware::Update(float dt)
{

	glGetIntegerv(GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &available_memory);
	glGetIntegerv(GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &dedicated_memory);
	memory_usage = total_memory - available_memory;

	return UPDATE_CONTINUE;
}

void Hardware::Draw()
{

	ImGui::Text("Platform: ");
	const char *plat = SDL_GetPlatform();
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0, 1, 0, 100), plat);
	// CPU
	ImGui::Text("CPUs: ");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0, 1, 0, 100), "%i (Cache: %i kB)", cpus, cache);

	//RAM
	ImGui::Text("System RAM: ");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0, 1, 0, 100), "%i MB", system_ram);

	// Caps
	ImGui::Text("Caps: ");
	
	ImGui::SameLine();
	if (rdtsc)
	{
		ImGui::TextColored(ImVec4(0, 1, 0, 100), "RDTSC");
		ImGui::SameLine();
	}

	if (mmx)
	{
		ImGui::TextColored(ImVec4(0, 1, 0, 100), "MMX");
		ImGui::SameLine();
	}


	if (sse)
	{
		ImGui::TextColored(ImVec4(0, 1, 0, 100), "SSE");
		ImGui::SameLine();
	}


	if (sse2)
	{
		ImGui::TextColored(ImVec4(0, 1, 0, 100), "SSE2");
		ImGui::SameLine();
	}

	if (sse3)
	{
		ImGui::TextColored(ImVec4(0, 1, 0, 100), "SSE3");
		ImGui::SameLine();
	}

	if (sse41)
	{
		ImGui::TextColored(ImVec4(0, 1, 0, 100), "SSE41");
		ImGui::SameLine();
	}

	if (sse42)
	{
		ImGui::TextColored(ImVec4(0, 1, 0, 100), "SSE42");
		ImGui::SameLine();
	}


	if (avx)
	{
		ImGui::TextColored(ImVec4(0, 1, 0, 100), "AVX");
	}
	
	// GPU
	ImGui::Separator();
	ImGui::Text("GPU: ");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0, 1, 0, 100), "%s", vendor);

	ImGui::Text("Brand: ");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0, 1, 0, 100), "%s", gpu_name);

	ImGui::Text("VRAM Usage: ");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0, 1, 0, 100), "%.2f MB", (memory_usage / 1000.0f));

	ImGui::Text("VRAM Budget: ");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0, 1, 0, 100), "%.2f MB", (total_memory / 1000.0f));

	ImGui::Text("VRAM Available: ");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0, 1, 0, 100), "%.2f MB", (available_memory / 1000.0f));
}
