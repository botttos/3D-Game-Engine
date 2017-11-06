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

ModuleImGui::ModuleImGui(bool start_enabled) : Module(start_enabled)
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
	ImGuiUpdate();
	
	return UPDATE_CONTINUE;
}

bool ModuleImGui::ImGuiUpdate() const
{	
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
		static bool show_console_window = true;
		static bool show_config_window = true;
		static bool show_inspector = true;
		static bool show_gameObjects_window = true;

		if(show_inspector)
		{
			Inspector();
		}
		if (show_gameObjects_window)
		{
			App->scene_intro->go_window_enabled = true;
		}
		else
		{
			App->scene_intro->go_window_enabled = false;
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
				if (ImGui::MenuItem("- Exit"))
				{
					App->input->Quit();
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Window"))
			{
				
				if (ImGui::BeginMenu("- Grid"))
				{
					if (ImGui::MenuItem("- Show grid"))
					{
						App->camera->ShowGrid();
					}
					if (ImGui::MenuItem("- Show axis"))
					{
						App->camera->ShowAxis();
					}
					ImGui::EndMenu();
				}

				ImGui::Separator();

				ImGui::Checkbox("Configuration", &show_config_window);
				ImGui::Checkbox("Show console", &show_console_window);
				ImGui::Checkbox("Show inspector", &show_inspector);
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

				if (ImGui::MenuItem("- Devil (v1.7.8)"))
				{
					ShellExecuteA(0, 0, "chrome.exe", " http://openil.sourceforge.net", 0, SW_SHOWMAXIMIZED);
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

				if (ImGui::MenuItem("- Assimp (v3.3.1)"))
				{
					ShellExecuteA(0, 0, "chrome.exe", "http://assimp.sourceforge.net/", 0, SW_SHOWMAXIMIZED);
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

				ImGui::Separator();
				if (ImGui::BeginMenu("- OpenGL info"))
				{
					ImGui::Text("Vendor: ");
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0, 1, 0, 100), "%s", glGetString(GL_VENDOR));

					ImGui::Text("Renderer: ");
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0, 1, 0, 100), "%s", glGetString(GL_RENDERER));

					ImGui::Text("OpenGL version supported: ");
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0, 1, 0, 100), "%s", glGetString(GL_VERSION));

					ImGui::Text("GLSL: ");
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0, 1, 0, 100), "%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		ImGui::Render();
	}

	(App->renderer3D->enable_wireframe) ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	
	return true;
}

bool ModuleImGui::Trigger(bool bolean)
{
	if (bolean == true)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void ModuleImGui::Inspector() const
{
	ImGui::Begin("Inspector");
	ImGui::SetWindowSize(ImVec2(500, 500), 0);

	ImGui::Text("Model Name: %s", App->fbx_loader->file_name.c_str());
	ImGui::Text("Model Path: %s", App->fbx_loader->path.c_str());

	if (ImGui::CollapsingHeader("Transform"), ImGuiTreeNodeFlags_DefaultOpen)
	{
		ImGui::Text("Showing read only information about the mesh transform");
		ImGui::Separator();

		ImGui::Text("Position");
		ImGui::Text("[%f]   [%f]   [%f]", App->fbx_loader->GetPosition().x, App->fbx_loader->GetPosition().y, App->fbx_loader->GetPosition().z);

		ImGui::Text("Rotation");
		ImGui::Text("[%f]   [%f]   [%f]", App->fbx_loader->GetRotation().x, App->fbx_loader->GetRotation().x, App->fbx_loader->GetRotation().x);

		ImGui::Text("Scale");
		ImGui::Text("[%f]   [%f]   [%f]", App->fbx_loader->GetScale().x, App->fbx_loader->GetScale().x, App->fbx_loader->GetScale().x);
		
	}

	if (ImGui::CollapsingHeader("Mesh information"), ImGuiTreeNodeFlags_DefaultOpen)
	{
		ImGui::Text("Showing read only information about the mesh");
		ImGui::Separator();
		ImGui::Text("Mesh triangles: %i", App->fbx_loader->GetVertices()/3);
		ImGui::Text("Mesh vertices: %i", App->fbx_loader->GetVertices());
		ImGui::Text("Mesh indices: %i", App->fbx_loader->GetIndices());
		ImGui::Text("Mesh normals: %f", App->fbx_loader->GetNormals());
		ImGui::Text("Mesh uvs: %f", App->fbx_loader->GetUvs());
	}

	if (ImGui::CollapsingHeader("Material"), ImGuiTreeNodeFlags_DefaultOpen)
	{
		ImGui::Text("Showing only read information about the mesh material");
		ImGui::Separator();
		if (App->fbx_loader->last_texture_id == 0)
			ImGui::Image((ImTextureID)App->fbx_loader->GetTextureId(), ImVec2(200, 200));
		else
			ImGui::Image((ImTextureID)App->fbx_loader->last_texture_id, ImVec2(200, 200));
	}
	if (ImGui::IsItemHovered() || (ImGui::IsRootWindowOrAnyChildFocused() && !ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0)))
		ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
	ImGui::End();
}