#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "imGUI\imgui.h"
#include "imGUI\imgui_impl_sdl_gl3.h"
#include "Glew\include\glew.h"

#pragma comment( lib, "Glew/libx86/glew32.lib" )

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	glewInit();
	ImGui_ImplSdlGL3_Init(App->window->window);
	//Testing the Appveyor
	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	ImGui_ImplSdlGL3_Shutdown();
	return true;
}

// PreUpdate
update_status ModuleSceneIntro::PreUpdate(float dt)
{
	ImGui_ImplSdlGL3_NewFrame(App->window->window);
	return(UPDATE_CONTINUE);
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	if (App->camera->active == true)
	{
		Plane p(0, 1, 0, 0);
		p.axis = true;
		p.Render();
	}

	// GUI update
	ImGuiUpdate();
	
	return UPDATE_CONTINUE;
}

bool ModuleSceneIntro::ImGuiUpdate()
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

	if (able_imgui == true)
	{

		static bool show_test_window = false;

		if (show_test_window)
		{
			ImGui::ShowTestWindow();
		}

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::Text("New file");
				ImGui::Text("Open file");
				ImGui::Separator();
				ImGui::Text("Save file");
				ImGui::Separator();
				if (ImGui::MenuItem("Hide GUI"))
				{
					able_imgui = false;
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Exit"))
				{
					App->input->Quit();
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit"))
			{
				ImGui::Text("Undo");
				ImGui::Text("Redo");
				ImGui::Separator();
				ImGui::Text("Cut");
				ImGui::Text("Copy");
				ImGui::Text("Paste");
				ImGui::Separator();
				ImGui::Text("Duplicate");
				ImGui::Text("Delete");
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Assets"))
			{
				ImGui::Text("Import new asset");
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("GameObject"))
			{
				ImGui::Text("Create empty");
				if (ImGui::BeginMenu("3D object"))
				{
					ImGui::Text("Cube");
					ImGui::Text("Sphere");
					ImGui::Text("Capsule");
					ImGui::Text("Cylinder");
					ImGui::Separator();
					ImGui::Text("Plane");
					ImGui::Text("Quad");
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Component"))
			{
				ImGui::Text("Mesh");
				ImGui::Text("Physics");
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Window"))
			{
				//We can use ImGui::Button("Show grid") to don't close the window automatically
				if (ImGui::MenuItem("Show grid"))
				{
					App->camera->ShowGrid();
				}



				ImGui::Separator();

				ImGui::Checkbox("Show test window", &show_test_window);

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("About"))
			{

				ImGui::EndMenu();
			}


			ImGui::EndMainMenuBar();
		}

		ImGui::Render();
	}
	return true;
}