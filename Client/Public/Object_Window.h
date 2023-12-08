#pragma once

#include "ImGui_Window.h"

BEGIN(Engine)
class CGameObject;
class GameInstance;
END

BEGIN(Client)
class CTerrain_MapTool;

class CObject_Window final :public CImGui_Window
{
	DECLARE_SINGLETON(CObject_Window)
public:
	CObject_Window();
	virtual ~CObject_Window() = default;
public:
	virtual HRESULT	Initialize();
	virtual void	Start();
	virtual void	Tick(_float fTimeDelta);
	virtual HRESULT	Render(ID3D11DeviceContext* pContext) override;
public:
	class CTerrain_MapTool* m_pTerrain = nullptr;
	class CGameInstance* m_pGameInstance = { nullptr };

public:
	json					m_ObjectJson;
public:
	virtual void Free() override;
};

END