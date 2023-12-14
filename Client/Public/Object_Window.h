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
	char* ConvertWCtoC(const wchar_t* str);
	wchar_t* ConvertCtoWC(const char* str);
public:
	void Create_Object(const wstring& strLayerTag, const wstring& strPrototypeTag);
	
public:
	vector<string>	Get_ObjectTag() { return m_vObjectTag; }
public:
	CTerrain_Tool*			m_pTerrain = nullptr;
	CGameInstance*			m_pGameInstance = { nullptr };
	CLevel_MapTool*			m_pLevel_MapTool = { nullptr };

public:
	vector<string>			m_vObjectTag;
	vector<CGameObject*>	m_CreateList;
public:
	json					m_ObjectJson;
	_bool					m_bguizmo =false;
	_bool					m_Terrain_Mesh = false;
	_bool					m_bCreateCheck = false;
	_bool					m_bDeleteCheck = false;
	_bool					m_bListCheck = false;

	_int					m_iCreateObjectSize = 0;
public:
	virtual void Free() override;
};

END