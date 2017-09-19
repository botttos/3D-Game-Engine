#include "Application.h"
#include "ModuleImGui.h"
#include "imGUI\imgui.h"
#include "imGUI\imgui_impl_sdl_gl3.h"
#include "Glew\include\glew.h"
#include "MathGeoLib\MathGeoLib.h"

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
	ImGui_ImplSdlGL3_Init(App->window->window);

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

	if (able_imgui == true)
	{
		static bool show_test_window = false;
		static bool createspheresandcollide = false;
		static bool createsphereandnotcollide = false;

		if (createspheresandcollide)
		{
			math::Sphere testsphere1;
			vec vector1(1.0f, 1.0f, 1.0f);
			testsphere1.pos = vector1;
			testsphere1.r = 5.0f;
			LOG("Sphere1 created");
			LOG("Sphere1 radius: %f", testsphere1.r);
			LOG("Sphere1 position: (%f, %f, %f)", testsphere1.pos.x, testsphere1.pos.y, testsphere1.pos.z);

			math::Sphere testsphere2;
			vec vector2(1.0f, 2.0f, 1.0f);
			testsphere2.pos = vector2;
			testsphere2.r = 5.0f;
			LOG("Sphere2 created");
			LOG("Sphere2 radius: %f", testsphere2.r);
			LOG("Sphere2 position: (%f, %f, %f)", testsphere2.pos.x, testsphere2.pos.y, testsphere2.pos.z);

			if (testsphere1.Intersects(testsphere2))
			{
				LOG("The spheres intersect.");
			}
			else
			{
				LOG("The spheres do not intersect.");
			}
		}

		if (createsphereandnotcollide)
		{
			math::Sphere testsphere3;
			vec vector3(5.0f, 5.0f, 5.0f);
			testsphere3.pos = vector3;
			testsphere3.r = 1.0f;
			LOG("Sphere3 created");
			LOG("Sphere3 radius: %f", testsphere3.r);
			LOG("Sphere3 position: (%f, %f, %f)", testsphere3.pos.x, testsphere3.pos.y, testsphere3.pos.z);

			math::Sphere testsphere4;
			vec vector4(1.0f, 1.0f, 1.0f);
			testsphere4.pos = vector4;
			testsphere4.r = 1.0f;
			LOG("Sphere4 created");
			LOG("Sphere4 radius: %f", testsphere4.r);
			LOG("Sphere4 position: (%f, %f, %f)", testsphere4.pos.x, testsphere4.pos.y, testsphere4.pos.z);

			if (testsphere3.Intersects(testsphere4))
			{
				LOG("The spheres intersect.");
			}
			else
			{
				LOG("The spheres do not intersect.");
			}
		}

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

				ImGui::Checkbox("Create test sphere collision", &createspheresandcollide);
				
				ImGui::Checkbox("Create test sphere no collision", &createsphereandnotcollide);

				ImGui::Separator();

				ImGui::Checkbox("Show test window", &show_test_window);

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("About"))
			{

				ImGui::Text("This is a 3D game engine made by Alexis Cosano and Fran Ruiz,\ntwo college students from the CITM UPC, Terrassa.\nThis engine is made for educational purposes.");
				ImGui::Separator();

				if (ImGui::MenuItem("Link to repository"))
				{
					ShellExecuteA(0, 0, "chrome.exe", "https://github.com/botttos/3D-Game-Engine", 0, SW_SHOWMAXIMIZED);
				}

				if (ImGui::MenuItem("Link to the latest release"))
				{
					ShellExecuteA(0, 0, "chrome.exe", "https://github.com/botttos/3D-Game-Engine/releases", 0, SW_SHOWMAXIMIZED);
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