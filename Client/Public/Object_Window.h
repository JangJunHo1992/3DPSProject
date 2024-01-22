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
	void Create_Object_On_Map(const wstring& strLayerTag, const wstring& strPrototypeTag);
	_bool Check_ImGui_Rect();
public://guizmo
	void ImGuizmo_Initialize();
	void Set_GuizmoCamProj();
	void Set_GuizmoCamView();
	void Setup_Guizmo();
	void Compress_Guizmo_Mode();
	ImGuizmo::OPERATION		mCurrentGizmoOperation;
	ImGuizmo::MODE			mCurrentGizmoMode;

public://guizmo 변수
	_float* m_arrView = { nullptr };
	_float* m_arrProj = { nullptr };
	_float  snap[3] = { 1.f,1.f,1.f }; //1틱 움직이는 거리
	_bool	useSnap = { false };

public:
	vector<string>	Get_ObjectTag() { return m_vObjectTag; }
public:
	CTerrain_Tool*			m_pTerrain = nullptr;
	class CMap_Tool*		m_pMap = { nullptr };
	CGameInstance*			m_pGameInstance = { nullptr };
	CLevel_MapTool*			m_pLevel_MapTool = { nullptr };
	CGameObject*			m_PickingObject = { nullptr };
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
	_bool					m_bCloneCount = false;

	_int					m_iCreateObjectSize = 0;
public:
	virtual void Free() override;
};

END