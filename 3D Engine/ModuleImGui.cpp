#include "Glew\include\glew.h"
#include "Application.h"
#include "ModuleImGui.h"
#include "imGUI\imgui.h"
#include "imGUI\imgui_impl_sdl_gl3.h"
#include "MathGeoLib\MathGeoLib.h"
#include "ModuleConsole.h"
#include "SDL\include\SDL_opengl.h"
#include "gl\GL.h"
#include "gl\GLU.h"

#pragma comment( lib, "Glew/libx86/glew32.lib" )

ModuleImGui::ModuleImGui(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleImGui::~ModuleImGui()
{}

// Load assets
bool ModuleImGui::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	glewInit();
	LOG("Using Glew %s", glewGetString(GLEW_VERSION));
	ImGui_ImplSdlGL3_Init(App->window->window);
	LOG("Loading Intro assets COMPLETE");
	return ret;
}

// Load assets
bool ModuleImGui::CleanUp()
{
	LOG("Unloading Intro scene");
	ImGui_ImplSdlGL3_Shutdown();
	return true;
}

// PreUpdate
update_status ModuleImGui::PreUpdate(float dt)
{
	ImGui_ImplSdlGL3_NewFrame(App->window->window);
	return(UPDATE_CONTINUE);
}

// Update
update_status ModuleImGui::Update(float dt)
{
	// GUI update
	ImGuiUpdate();

	return UPDATE_CONTINUE;
}

bool ModuleImGui::ImGuiUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
	{
		if (able_imgui == false)
		{
			able_imgui = true;
			ImGui_ImplSdlGL3_Init(App->window->window);
		}
		else
		{
			able_imgui = false;
			ImGui_ImplSdlGL3_Shutdown();
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN)
	{
		if (App->console->active == false)
		{
			App->console->active = true;

		}
		else
		{
			App->console->active = false;
		}
	}
	
	if (App->console->active == true)
	{
		App->console->Draw("Console");
	}

	if (App->config->active == true)
	{
		App->config->Draw("Configuration");
	}

	if (able_imgui == true)
	{
		static bool show_test_window = false;
		static bool show_console_window = false;
		static bool show_config_window = false;

		if (show_test_window)
		{
			ImGui::ShowTestWindow();
		}

		if (show_console_window)
		{
			App->console->active = true;
		}
		else
		{
			App->console->active = false;
		}

		if (show_config_window)
		{
			App->config->active = true;
		}
		else
		{
			App->config->active = false;
		}

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::Text("- New file");
				ImGui::Text("- Open file");
				ImGui::Separator();
				ImGui::Text("- Save file");
				ImGui::Separator();
				if (ImGui::MenuItem("- Hide GUI"))
				{
					able_imgui = false;
				}
				ImGui::Separator();
				if (ImGui::MenuItem("- Exit"))
				{
					App->input->Quit();
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit"))
			{
				ImGui::Text("- Undo");
				ImGui::Text("- Redo");
				ImGui::Separator();
				ImGui::Text("- Cut");
				ImGui::Text("- Copy");
				ImGui::Text("- Paste");
				ImGui::Separator();
				ImGui::Text("- Duplicate");
				ImGui::Text("- Delete");
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Assets"))
			{
				ImGui::Text("- Import new asset");
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("GameObject"))
			{
				ImGui::Text("- Create empty");
				if (ImGui::BeginMenu("- 3D object"))
				{
					ImGui::Text("- Cube");
					if (ImGui::BeginMenu("- Sphere"))
					{
						if (ImGui::MenuItem("- Create test sphere collision"))
						{
							math::Sphere testsphere1;
							vec vector1(1.0f, 1.0f, 1.0f);
							testsphere1.pos = vector1;
							testsphere1.r = 5.0f;
							App->console->AddLog("----------------------------");
							App->console->AddLog("Sphere1 created");
							App->console->AddLog("Sphere1 radius: %f", testsphere1.r);
							App->console->AddLog("Sphere1 position: (%f, %f, %f)", testsphere1.pos.x, testsphere1.pos.y, testsphere1.pos.z);

							math::Sphere testsphere2;
							vec vector2(1.0f, 2.0f, 1.0f);
							testsphere2.pos = vector2;
							testsphere2.r = 5.0f;
							App->console->AddLog("Sphere2 created");
							App->console->AddLog("Sphere2 radius: %f", testsphere2.r);
							App->console->AddLog("Sphere2 position: (%f, %f, %f)", testsphere2.pos.x, testsphere2.pos.y, testsphere2.pos.z);

							if (testsphere1.Intersects(testsphere2))
							{
								App->console->AddLog("The spheres intersect.");
							}
							else
							{
								App->console->AddLog("The spheres do not intersect.");
							}
						}

						if (ImGui::MenuItem("- Create test sphere no collision"))
						{
							math::Sphere testsphere3;
							vec vector3(5.0f, 5.0f, 5.0f);
							testsphere3.pos = vector3;
							testsphere3.r = 1.0f;
							App->console->AddLog("----------------------------");
							App->console->AddLog("Sphere3 created");
							App->console->AddLog("Sphere3 radius: %f", testsphere3.r);
							App->console->AddLog("Sphere3 position: (%f, %f, %f)", testsphere3.pos.x, testsphere3.pos.y, testsphere3.pos.z);

							math::Sphere testsphere4;
							vec vector4(1.0f, 1.0f, 1.0f);
							testsphere4.pos = vector4;
							testsphere4.r = 1.0f;
							App->console->AddLog("Sphere4 created");
							App->console->AddLog("Sphere4 radius: %f", testsphere4.r);
							App->console->AddLog("Sphere4 position: (%f, %f, %f)", testsphere4.pos.x, testsphere4.pos.y, testsphere4.pos.z);

							if (testsphere3.Intersects(testsphere4))
							{
								App->console->AddLog("The spheres intersect.");
							}
							else
							{
								App->console->AddLog("The spheres do not intersect.");
							}
						}
						ImGui::EndMenu();
					}
					ImGui::Text("- Capsule");
					ImGui::Text("- Cylinder");
					ImGui::Separator();
					ImGui::Text("- Plane");
					ImGui::Text("- Quad");
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Component"))
			{
				ImGui::Text("- Mesh");
				ImGui::Text("- Physics");
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Window"))
			{
				//We can use ImGui::Button("Show grid") to don't close the window automatically
				if (ImGui::MenuItem("- Show grid"))
				{
					App->camera->ShowGrid();
				}
				ImGui::Separator();
				ImGui::Checkbox("Show console", &show_console_window);
				ImGui::Checkbox("Show test window", &show_test_window);
				ImGui::Checkbox("Config", &show_config_window);
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("About"))
			{
				ImGui::TextColored(ImVec4(1, 1, 0, 100), "=== Coolgine 3D ===");
				ImGui::Text("This is a 3D game engine made by Alexis Cosano and Fran Ruiz,\ntwo college students from the CITM UPC, Terrassa.\nThis engine is made for educational purposes.");
				ImGui::Separator();
				ImGui::TextColored(ImVec4(0, 1, 1, 100), "Project links");
				if (ImGui::MenuItem("- Link to Coolgine 3D repository"))
				{
					ShellExecuteA(0, 0, "chrome.exe", "https://github.com/botttos/3D-Game-Engine", 0, SW_SHOWMAXIMIZED);
				}

				if (ImGui::MenuItem("- Link to the latest release"))
				{
					ShellExecuteA(0, 0, "chrome.exe", "https://github.com/botttos/3D-Game-Engine/releases", 0, SW_SHOWMAXIMIZED);
				}
				ImGui::Separator();
				ImGui::TextColored(ImVec4(0, 1, 0, 100), "=== Libraries used ===");
				if (ImGui::MenuItem("- ImGui (v1.52)"))
				{
					ShellExecuteA(0, 0, "chrome.exe", "https://github.com/ocornut/imgui", 0, SW_SHOWMAXIMIZED);
				}

				if (ImGui::MenuItem("- Brofiler (v1.1.2)"))
				{
					ShellExecuteA(0, 0, "chrome.exe", "http://www.brofiler.com/", 0, SW_SHOWMAXIMIZED);
				}
				
				if (ImGui::MenuItem("- Parson"))
				{
					ShellExecuteA(0, 0, "chrome.exe", "http://kgabis.github.io/parson/", 0, SW_SHOWMAXIMIZED);
				}

				if (ImGui::MenuItem("- MathGeoLib (v2.0)"))
				{
					ShellExecuteA(0, 0, "chrome.exe", "http://clb.demon.fi/MathGeoLib/nightly/", 0, SW_SHOWMAXIMIZED);
				}

				if (ImGui::MenuItem("- mmgr"))
				{
					ShellExecuteA(0, 0, "chrome.exe", "http://www.flipcode.com/archives/Presenting_A_Memory_Manager.shtml", 0, SW_SHOWMAXIMIZED);
				}

				ImGui::AlignFirstTextHeightToWidgets();
				ImGui::Text("You can download it from"); ImGui::SameLine(); 
				if (ImGui::Button("here", ImVec2(40, 20)))
				{
					ShellExecuteA(0, 0, "chrome.exe", "http://www.stratos-ad.com/forums/index.php?topic=9897.0", 0, SW_SHOWMAXIMIZED);
				}
				ImGui::Text("Just look for the first comment from the user:"); ImGui::SameLine();
				ImGui::TextColored(ImVec4(1, 1, 0, 100), "Astat");

				if (ImGui::MenuItem("- Bullet (v2.84)"))
				{
					ShellExecuteA(0, 0, "chrome.exe", "http://bulletphysics.org/wordpress/", 0, SW_SHOWMAXIMIZED);
				}

				if (ImGui::MenuItem("- Glew (v2.0.0)"))
				{
					ShellExecuteA(0, 0, "chrome.exe", "http://glew.sourceforge.net/", 0, SW_SHOWMAXIMIZED);
				}
				if (ImGui::MenuItem("- GLUT (v3.7)"))
				{
					ShellExecuteA(0, 0, "chrome.exe", "https://www.opengl.org/resources/libraries/glut/", 0, SW_SHOWMAXIMIZED);
				}

				if (ImGui::MenuItem("- SDL (v2.0.6)"))
				{
					ShellExecuteA(0, 0, "chrome.exe", "https://www.libsdl.org/", 0, SW_SHOWMAXIMIZED);
				}

				if (ImGui::MenuItem("- SDL_mixer (v2.0.0)"))
				{
					ShellExecuteA(0, 0, "chrome.exe", "https://www.libsdl.org/projects/SDL_mixer/", 0, SW_SHOWMAXIMIZED);
				}
				ImGui::Separator();
				ImGui::Text("=== License ===");
				ImGui::TextWrapped("Coolgine 3D is under The MIT License, see LICENSE for more information.");
				if (ImGui::MenuItem("- The MIT License (MIT)"))
				{
					ShellExecuteA(0, 0, "chrome.exe", "https://opensource.org/licenses/mit-license.php", 0, SW_SHOWMAXIMIZED);
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("RandomNumbers"))
			{

				ImGui::Text("Random number button between 1 and 100.");
				ImGui::Separator();

				LCG rand_number;
				if (ImGui::Button(" PRESS ME "))
				{
					rand = rand_number.Int(0, 100);
				}
				ImGui::Text("%i", rand);


				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}



		ImGui::Render();
	}
	return true;
}