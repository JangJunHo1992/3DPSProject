#pragma once

namespace Client 
{
	static const unsigned int	g_iWinSizeX = 1280;
	static const unsigned int	g_iWinSizeY = 720;

	enum LEVEL { LEVEL_STATIC, LEVEL_LOGO, LEVEL_GAMEPLAY,LEVEL_TOOL, LEVEL_LOADING,LEVEL_STAGE1,LEVEL_BOSS1,LEVEL_BOSS2, LEVEL_EFFECT_TOOL, LEVEL_END };
}

using namespace Client;


extern HWND g_hWnd;
extern HINSTANCE g_hInst;


