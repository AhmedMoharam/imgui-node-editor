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
	float RSI(const char *, int);
	float OBV(const char *stock, const char *start_date, const char *end_date, int days);
	float MACD(const char *stock, const char *start_date, const char *end_date, const char *price_name, int period1, int period2, int period3);
	float IchimokuCloud(const char *stock, const char *start_date, const char *end_date);
	float WILLIAMS(const char *stock, const char *start_date, const char *end_date, int days);
	char const * backtesting(const char * stockName, const char * algoName, float buyValue, float sellValue, const char * startDate, const char * endDate, float commission);
	char const * IBKR(const char *ip, int port, int clientid,const char * tick,const char * action,int quantity,const char * orderType,float tradePrice,float stoploss,float profitTarget);
}