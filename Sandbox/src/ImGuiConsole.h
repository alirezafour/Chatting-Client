#pragma once
#include "imgui.h"
#include "Client.h"

class ImGuiConsole
{
public:
	ImGuiConsole();
	~ImGuiConsole();

	// Portable helpers
	static int   Stricmp(const char* s1, const char* s2);
	static int   Strnicmp(const char* s1, const char* s2, int n);
	static char* Strdup(const char* s);
	static void  Strtrim(char* s);

	void ClearLog();

	void AddLog(const char* fmt, ...) IM_FMTARGS(2);

	void Draw(const char* title, bool* p_open);

	void ExecCommand(const char* command_line);

	// In C++11 you'd be better off using lambdas for this sort of forwarding callbacks
	static int TextEditCallbackStub(ImGuiInputTextCallbackData* data);

	int TextEditCallback(ImGuiInputTextCallbackData* data);

private:
	char                  InputBuf[256];
	ImVector<char*>       Items;
	ImVector<const char*> Commands;
	ImVector<char*>       History;
	int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
	ImGuiTextFilter       Filter;
	bool                  AutoScroll;
	bool                  ScrollToBottom;

	Client m_Client;

};


