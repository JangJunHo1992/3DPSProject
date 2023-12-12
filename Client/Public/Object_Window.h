#pragma once

#include "ImGui_Window.h"

BEGIN(Engine)
class CGameObject;
class GameInstance;
END

BEGIN(Client)
class CTerrain_Tool;
class CLevel_MapTool;

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
	void Set_LevelTool(CLevel_MapTool* _LevelMapTool);
public:
	char* ConverWStringtoC(const wstring& wstr);

public:
	class CTerrain_Tool* m_pTerrain = nullptr;
	class CGameInstance* m_pGameInstance = { nullptr };
	CLevel_MapTool*		 m_pLevel_MapTool = { nullptr };

public:
	vector<string>			m_vObjectTag;
	vector<_uint>			m_CreateIndex;
public:
	json					m_ObjectJson;
	_bool					m_bguizmo =false;
	_bool					m_Terrain_Mesh = false;
public:
	virtual void Free() override;
};

END