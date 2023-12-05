#pragma once

#include "ImGui_Window.h"

BEGIN(Engine)
class CGameObject;
END

BEGIN(Client)
class CTerrain;

class CMap_Window final : public CImGui_Window
{
	DECLARE_SINGLETON(CMap_Window)
public:

};

END