#pragma once
#include "Client_Defines.h"
#include "Base.h"

BEGIN(Engine)
class CGameObject;
END

BEGIN(Client)

class CImGui_Window;
class CTerrain;

class CImgui_Manager  : public CBase
{
public:
	enum class IMGUI_WINDOW_TYPE
	{
		IMGUI_UIVIEW,
		IMGUI_PROTOTYPEVIEW,
		IMGUI_HIERARCHYVIEW,
		IMGUI_COMPONENTVIEW,
		IMGUI_END
	};

	enum class EDITER_TYPE
	{
		SCENE,
		EFFECT,
		MODEL,
		TYPE_END
	};
	DECLARE_SINGLETON(CImgui_Manager)
private:
	CImgui_Manager() = default;
	virtual	~CImgui_Manager() = default;

public:
	HRESULT SetUp_Imgui(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	void	Tick(_float fTimeDelta);
	void	Render();

public:
	void Save_EffectJson();
public:
	_bool Open_File(string& Out_szSelectedFile, string& Out_szFilePath);
private:
	void Init_SceneEditer();
	void Init_EffectEditer();
	void Init_ModelEditer();

	//void Release_CurrentEditer();
	void Write_Json(const string& In_szPath);
	void Load_FromJson(const string& In_szPath);

	void Toggle_PhysXInfo();

public:
	virtual void Free() override;

private:
	char*	ConvertWCtoC(const wchar_t* str);
	wchar_t* ConvertCtoWC(const char* str);

private:
	_bool				 m_bMainTool = { true };
	_bool				 m_bMapTool, m_bEffectTool, m_bObjectTool, m_bCameraTool = { false };
	_bool				 m_StartImgui = true;

private:
	void	HelpMarker(const char* desc);
	char* ConverWStringtoC(const wstring& wstr);

private:
	void	ShowMapTool();
	void	ShowEffectTool();
	void	ShowObjectTool();
	void	ShowCameraTool();
private:


public:
	vector<shared_ptr<CImGui_Window>> m_arrWindows;

private: /* For Json */
	string m_szJsonPath = "../Bin/LevelData/";
	string m_szCurrentLocalPath;
	//rapid m_CurrentLevelJson;

	EDITER_TYPE m_eCurrentEditerType = EDITER_TYPE::TYPE_END;

private: /* For Effect Editer */
	weak_ptr<CTerrain>		m_pTerrain;

private: /* For. PhysXInfo */
	_bool					m_bViewPhysXInfo = false;

};

END
