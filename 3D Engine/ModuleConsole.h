#ifndef __ModuleConsole_H__
#define __ModuleConsole_H__

#include "Application.h"
#include "Module.h"
#include "Globals.h"
#include "imGUI\imgui.h"

class Console : public Module
{
public:
	Console(Application* app, bool start_enabled = true);
	~Console();
	
	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void AddLog(const char*, ...) IM_FMTARGS(2);
	void ClearLog();

	void Draw(const char* title);

	void ExecCommand(const char* command_line);

	static int TextEditCallbackStub(ImGuiTextEditCallbackData* data); // In C++11 you are better off using lambdas for this sort of forwarding callbacks
	int TextEditCallback(ImGuiTextEditCallbackData* data); // In C++11 you are better off using lambdas for this sort of forwarding callbacks

private:

	char                  InputBuf[256];
	ImVector<char*>       Items;
	bool                  ScrollToBottom;
	ImVector<char*>       History;
	int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
	ImVector<const char*> Commands;
	
	static int   Stricmp(const char* str1, const char* str2) { int d; while ((d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; } return d; }
	static char* Strdup(const char *str) { size_t len = strlen(str) + 1; void* buff = malloc(len); return (char*)memcpy(buff, (const void*)str, len); }
};

#endif 