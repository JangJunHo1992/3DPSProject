#include "stdafx.h"

#include "../../Reference/Imgui/imgui.h"
#include "../../Reference/Imgui/imgui_impl_win32.h"
#include "../../Reference/Imgui/imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>

#include "Imgui_Manager.h"
#include "Map_Window.h"
#include "Object_Window.h"
#include "Camera_Window.h"
#include "Effect_Window.h"

#include "Camera_Dynamic.h"
#include "GameInstance.h"

IMPLEMENT_SINGLETON(CImgui_Manager)

HRESULT CImgui_Manager::SetUp_Imgui(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	m_pDevice = pDevice;
	m_pContext = pContext;
	Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pContext);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	//io.ConfigViewportsNoAutoMerge = true;

	ImGui::StyleColorsDark();

	//ImGui::StyleColorsClassic();

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplWin32_Init(g_hWnd);
	ImGui_ImplDX11_Init(pDevice, pContext);
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\malgun.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesKorean());
	
	Init_Window();
	
	
	return S_OK;
}

void CImgui_Manager::Tick(_float fTimeDelta)
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoBackground;
	CheckPicking(m_ePickMode);
}

void CImgui_Manager::Render()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;
	if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::SetNextWindowSize(ImVec2(g_iWinSizeX, g_iWinSizeY), ImGuiCond_Always);
	ImGui::Begin("Dock", nullptr, window_flags);
	ImGui::PopStyleVar(2);
	ImGuiID dockspaceID = ImGui::GetID("DockSpace");
	ImGui::DockSpace(dockspaceID, ImVec2(0, 0), dockspaceFlags);
	ImGui::End();

	if (ImGui::BeginMainMenuBar())
	{
		if (m_bMapTool)	ShowMapTool();
		if (m_bEffectTool) ShowEffectTool();
		if (m_bObjectTool) ShowObjectTool();
		if (m_bCameraTool) ShowCameraTool();

		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save"))
			{
				m_pGameInstance->Save_Objects_With_Json(LEVEL::LEVEL_TOOL, "Test1");
			}
			if (ImGui::MenuItem("Load"))
			{
				Load_Objects_With_Json(LEVEL::LEVEL_TOOL, "Test1");

			}
	
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("PhysX_Collider", "PgUp"))
			{
				


			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Level"))
		{
			//���Ŀ� Level ����� ���⿡ �־ ���� �ְ� ���� 



			ImGui::EndMenu();
		}
		
		if (ImGui::BeginMenu("Editer"))
		{
			ImGui::RadioButton("NO_PICKING", &m_ePickMode, 0); ImGui::SameLine();
			ImGui::RadioButton("TERRAIN_PICKING", &m_ePickMode, 1); ImGui::SameLine();
			ImGui::RadioButton("MESH_PICKING", &m_ePickMode, 2);

			if (ImGui::MenuItem(u8"����","",&m_bMapTool))
			{
				
			}
			if (ImGui::MenuItem(u8"����Ʈ��", "", &m_bEffectTool))
			{

			}
			if (ImGui::MenuItem(u8"������Ʈ��", "", &m_bObjectTool))
			{

			}
			if (ImGui::MenuItem(u8"ī�޶���","", &m_bCameraTool))
			{
			}

			ImGui::EndMenu();
			

		}

		ImGui::EndMainMenuBar();
	}
	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void CImgui_Manager::Save_EffectJson()
{
}

_bool CImgui_Manager::Open_File(string& Out_szSelectedFile, string& Out_szFilePath)
{
	return _bool();
}

void CImgui_Manager::Init_SceneEditer()
{
}

void CImgui_Manager::Init_EffectEditer()
{
}

void CImgui_Manager::Init_ModelEditer()
{
}

void CImgui_Manager::Write_Json(const string& In_szPath)
{
	
}

void CImgui_Manager::Load_FromJson(const string& In_szPath)
{
}

HRESULT CImgui_Manager::Load_Objects_With_Json(_uint iLevelIndex, string filePath)
{
	json json_in;
	m_pGameInstance->Load_Json(filePath, json_in);

	for (auto& item : json_in.items())
	{
		json object = item.value();

		string tagObject = "Prototype_GameObject_";

		string targetName = object["Name"];
		tagObject += targetName;

		string tagLayer;

		if (targetName == "Camera")
		{
			tagObject += "_Dynamic";
			tagLayer = "Layer_Camera";
		}
		else if (targetName == "Terrain")
		{
			tagLayer = "Layer_BackGround";
			tagObject += "_Tool";
		}
		else
		{
			tagObject += "_Tool";
			tagLayer = "Layer_Monster";
		}

		wstring wStringLayerTag;
		wStringLayerTag.assign(tagLayer.begin(), tagLayer.end());

		wstring wStringObjTag;
		wStringObjTag.assign(tagObject.begin(), tagObject.end());

		_bool test = false;

		if ("Layer_Camera" == tagLayer)
		{
			CCamera_Dynamic::DYNAMIC_CAMERA_DESC		Desc = {};

			Desc.fMouseSensor = 0.05f;
			Desc.vEye = _float4(0.f, 20.f, -15.f, 1.f);
			Desc.vAt = _float4(0.f, 0.f, 0.f, 1.f);
			Desc.fFovy = XMConvertToRadians(60.0f);
			Desc.fAspect = (_float)g_iWinSizeX / g_iWinSizeY;
			Desc.fNear = 0.1f;
			Desc.fFar = 1000.f;
			Desc.fSpeedPerSec = 20.f;
			Desc.fRotationPerSec = XMConvertToRadians(180.0f);

			if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_TOOL, wStringLayerTag, TEXT("Prototype_GameObject_Camera_Dynamic"), &Desc)))
				return E_FAIL;
		}
		else
		{
			if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_TOOL, wStringLayerTag, wStringObjTag)))
				return E_FAIL;

			list<CGameObject*>* pGameObjects = m_pGameInstance->Get_GameObjects(LEVEL_TOOL, wStringLayerTag);
			if (nullptr == pGameObjects)
				continue;

			CGameObject* pGameObject = pGameObjects->back();
			if (nullptr == pGameObject)
				continue;

			_float4x4 WorldMatrix;
			ZeroMemory(&WorldMatrix, sizeof(_float4x4));
			CJson_Utility::Load_JsonFloat4x4(object["Component"]["Transform"], WorldMatrix);

			pGameObject->Set_WorldMatrix(WorldMatrix);
		}

	}

	return S_OK;
}

void CImgui_Manager::Toggle_PhysXInfo()
{
}



_int CImgui_Manager::CheckPicking(_int ePickMode)
{
	switch (m_ePickMode)
	{
	case NO_PICKING:
		
		break;
	case TERRAIN_PICKING:

		break;
	case MESH_PICKING:

		break;
	
	
	}
	return ePickMode;
}

void CImgui_Manager::Free()
{
	__super::Free();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	Safe_Release(m_pDevice);
	Safe_Release(m_pContext);

}

char* CImgui_Manager::ConvertWCtoC(const wchar_t* str)
{
	//��ȯ�� char* ���� ����
	char* pStr;
	//�Է¹��� wchar_t ������ ���̸� ����
	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	//char* �޸� �Ҵ�
	pStr = new char[strSize];
	//�� ��ȯ
	WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);
	return pStr;
}

wchar_t* CImgui_Manager::ConvertCtoWC(const char* str)
{
	//wchar_t�� ���� ����
	wchar_t* pStr;
	//��Ƽ ����Ʈ ũ�� ��� ���� ��ȯ
	int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);
	//wchar_t �޸� �Ҵ�
	pStr = new WCHAR[strSize];
	//�� ��ȯ
	MultiByteToWideChar(CP_ACP, 0, str, (int)strlen(str) + 1, pStr, strSize);
	return pStr;
}



void CImgui_Manager::ShowMapTool()
{
	m_pMapWindow->Render(m_pContext);

}



void CImgui_Manager::ShowEffectTool()
{
	ImGui::Begin(u8"����Ʈ��");
	if (ImGui::BeginTabBar("##EffectTabBar"))
	{
		//TODO ����Ʈ �� ����
		if (ImGui::BeginTabItem(u8"����Ʈ"))
		{
			ImGui::Text(u8"����Ʈ");
			ImGui::EndTabItem();
		}
		//TODO ����Ʈ �� ����

		//! ��ƼŬ �� ����
		if (ImGui::BeginTabItem(u8"��ƼŬ"))
		{
			ImGui::Text(u8"��ƼŬ");
			ImGui::EndTabItem();
		}
		//! ��ƼŬ �� ����
		ImGui::EndTabBar();
	}
	ImGui::End();
}

void CImgui_Manager::ShowObjectTool()
{
	m_pObjWindow->Render(m_pContext);
}

void CImgui_Manager::ShowCameraTool()
{
	ImGui::Begin(u8"ī�޶���");
	if (ImGui::BeginTabBar("##CameraTabBar"))
	{
		//TODO ������ �� ����
		if (ImGui::BeginTabItem(u8"������"))
		{
			ImGui::Text(u8"������");
			ImGui::EndTabItem();
		}
		//TODO ������ �� ����

		//! �޴��� �� ����
		if (ImGui::BeginTabItem(u8"�޴���"))
		{
			ImGui::Text(u8"�޴���");
			ImGui::EndTabItem();
		}
		//! �޴��� �� ����
		ImGui::EndTabBar();
	}
	ImGui::End();
}

void CImgui_Manager::Init_Window()
{
	m_pGameInstance = CGameInstance::GetInstance();
	m_pMapWindow = CMap_Window::GetInstance();
	m_pMapWindow->Initialize();
	m_pObjWindow = CObject_Window::GetInstance();
	m_pObjWindow->Initialize();
}


void CImgui_Manager::HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::TextUnformatted(desc);
		ImGui::EndTooltip();
	}
}

char* CImgui_Manager::ConverWStringtoC(const wstring& wstr)
{
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);

	char* result = new char[size_needed];

	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, result, size_needed, NULL, NULL);

	return result;
}

