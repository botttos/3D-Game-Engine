#include "ModuleConfig.h"

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

void Config::Draw(const char * title)
{
	ImGui::Begin(title);

	ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
	static bool show_application = false;

	ImGui::TextWrapped("Config Menu");
	ImGui::Separator();

	if (ImGui::CollapsingHeader("Application"))
	{
		ImGui::TextWrapped("App Name: Coolgine");
		ImGui::TextWrapped("Organization: UPC CITM");
		//ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		
		ImGui::Separator();
		ImGui::SliderInt("Max FPS", &fps, 0, 60, NULL);
		ImGui::TextWrapped("Limit Framerate: %i", fps);
		//FPS Graph
		for (uint i = 0; i < GRAPH_ARRAY_SIZE; i++)
		{
			fps_array[i] = fps_array[i + 1];
		}
		fps_array[GRAPH_ARRAY_SIZE - 1] = ImGui::GetIO().Framerate;
		char fps_title[25];
		sprintf_s(fps_title, 25, "Framerate %.1f", fps_array[29]);
		ImGui::PlotHistogram("", fps_array, IM_ARRAYSIZE(fps_array), 30, fps_title, 0.0f, 130.0f, ImVec2(0, 80));
		
		//MS Graph
		for (uint i = 0; i < GRAPH_ARRAY_SIZE; i++)
		{
			ms_array[i] = ms_array[i + 1];
		}
		ms_array[GRAPH_ARRAY_SIZE - 1] = 1000.0f / ImGui::GetIO().Framerate;
		char ms_title[25];
		sprintf_s(ms_title, 25, "Milliseconds %.1f", ms_array[29]);
		ImGui::PlotHistogram("", ms_array, IM_ARRAYSIZE(ms_array), 30, ms_title, 0.0f, 130.0f, ImVec2(0, 80));

	}


	ImGui::End();
}
