#include "ModuleConfig.h"
#include "ModuleWindow.h"
#include "Application.h"

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))


Config::Config(Application * app, bool start_enabled) : Module(app, start_enabled)
{
	ClearLog();
	memset(InputBuf, 0, sizeof(InputBuf));
	HistoryPos = -1;
  // "classify" is here to provide an example of "C"+[tab] completing to "CL" and displaying matches.
}

Config::~Config()
{
	ClearLog();
	for (int i = 0; i < History.Size; i++)
		free(History[i]);
}

bool Config::Start()
{
	return true;
}

update_status Config::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool Config::CleanUp()
{
	return true;
}

void Config::ClearLog()
{
	for (int i = 0; i < Items.Size; i++)
		free(Items[i]);
	Items.clear();
	ScrollToBottom = true;
}

int Config::GetFPS()
{
	return fps;
}

void Config::Draw(const char * title)
{
	ImGui::Begin(title);

	ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
	static bool show_application = false;

	ImGui::TextWrapped("Config Menu");
	ImGui::Separator();

	ImGui::Separator();
	if (ImGui::CollapsingHeader("Application"))
	{
		ImGui::TextWrapped("App Name: Coolgine");
		ImGui::TextWrapped("Organization: UPC CITM");
		//ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		
		ImGui::Separator();
		ImGui::SliderInt("Max FPS", &fps, 0, 60, NULL);
		ImGui::TextWrapped("Limit Framerate: %i", fps);
		if (fps > 60) fps = 0;
		//FPS Graph
		for (uint i = 0; i < GRAPH_ARRAY_SIZE; i++)
		{
			fps_array[i] = fps_array[i + 1];
		}
		fps_array[GRAPH_ARRAY_SIZE - 1] = ImGui::GetIO().Framerate;
		char fps_title[25];
		sprintf_s(fps_title, 25, "Framerate %.1f", fps_array[GRAPH_ARRAY_SIZE-1]);
		ImGui::PlotHistogram("", fps_array, IM_ARRAYSIZE(fps_array), 30, fps_title, 0.0f, 130.0f, ImVec2(0, 80));
		
		//MS Graph
		for (uint i = 0; i < GRAPH_ARRAY_SIZE; i++)
		{
			ms_array[i] = ms_array[i + 1];
		}
		ms_array[GRAPH_ARRAY_SIZE - 1] = 1000.0f / ImGui::GetIO().Framerate;
		char ms_title[25];
		sprintf_s(ms_title, 25, "Milliseconds %.1f", ms_array[GRAPH_ARRAY_SIZE-1]);
		ImGui::PlotHistogram("", ms_array, IM_ARRAYSIZE(ms_array), 30, ms_title, 0.0f, 130.0f, ImVec2(0, 80));

	}

	if (ImGui::CollapsingHeader("Window"))
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImGui::DragFloat("Global Alpha", &style.Alpha, 0.005f, 0.20f, 1.0f, "%.2f");

		ImGui::SliderFloat("Brightness", &brightness, 0, 2, NULL);

		ImGui::SliderInt("Width", &width, 0, 1920, NULL);
		
		ImGui::SliderInt("Height", &height, 0, 1080, NULL);
		

		if (ImGui::Checkbox("Fullscreen", &App->window->fullscreen))
		{
			App->window->SetFullScreen(&App->window->fullscreen);
		}

		if (ImGui::Checkbox("Windowed", &App->window->windowed))
		{
			App->window->SetWindowed(&App->window->windowed);
		}

		if (ImGui::Checkbox("Full Desktop", &App->window->full_desktop))
		{
			App->window->SetWindowFullDesktop();
			width = 1920;
			height = 1080;
		}

		
		if (ImGui::Button("Apply"))
		{
			// Window size
			App->window->SetWindowSize(width, height);

			// Brigthness
			App->window->SetWindowBrigthness(brightness);
		}

	}
	if (ImGui::CollapsingHeader("Hardware"))
	{
		App->hardware->Draw();
	}

	if (ImGui::CollapsingHeader("Volume"))
	{

		ImGui::SliderInt("Volume", &volume, 0, 100, NULL);

		if (ImGui::Checkbox("Mute", &mute))
		{

		}

		if (ImGui::Button("Apply"))
		{

		}

	}


	ImGui::End();
}
