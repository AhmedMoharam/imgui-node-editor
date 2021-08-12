#pragma once
#include <imgui.h>
ImTextureID Application_LoadTexture(const char* path);
ImTextureID Application_CreateTexture(const void* data, int width, int height);
void        Application_DestroyTexture(ImTextureID texture);
int         Application_GetTextureWidth(ImTextureID texture);
int         Application_GetTextureHeight(ImTextureID texture);

const char* Application_GetName();
void Application_Initialize();
void Application_Finalize();
void Application_Frame();

namespace py {
	float RSI(const char *);
	float OBV(const char *stock, const char *start_date, const char *end_date);
	float MACD(const char *stock, const char *start_date, const char *end_date);
	float IchimokuCloud(const char *stock, const char *start_date, const char *end_date);
	float WILLIAMS(const char *stock, const char *start_date, const char *end_date);
}
