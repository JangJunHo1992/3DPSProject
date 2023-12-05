#include "stdafx.h"

#include "../../Reference/Imgui/imgui.h"
#include "../../Reference/Imgui/imgui_impl_win32.h"
#include "../../Reference/Imgui/imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>

#include "Imgui_Manager.h"

IMPLEMENT_SINGLETON(CImgui_Manager)

HRESULT CImgui_Manager::SetUp_Imgui(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
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
	

	return S_OK;
}

void CImgui_Manager::Tick(_float fTimeDelta)
{

	/*ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoBackground;

	auto& style = ImGui::GetStyle();
	ImVec4* colors = style.Colors;

	const ImVec4 bgColor = ImVec4(0.1, 0.1, 0.1, 0.5);
	colors[ImGuiCol_WindowBg] = bgColor;
	colors[ImGuiCol_ChildBg] = bgColor;
	colors[ImGuiCol_TitleBg] = bgColor;*/
	

	//ImGui::Begin(u8"���� ��", &m_bMainTool, ImGuiWindowFlags_AlwaysAutoResize);

	//if (ImGui::BeginMenu(u8"��"))
	//{
	//	ImGui::MenuItem(u8"����", NULL, &m_bMapTool);
	//	ImGui::MenuItem(u8"����Ʈ��", NULL, &m_bEffectTool);
	//	ImGui::MenuItem(u8"������Ʈ��", NULL, &m_bObjectTool);
	//	ImGui::MenuItem(u8"ī�޶���", NULL, &m_bCameraTool);

	//	ImGui::EndMenu();
	//}

	//if (m_bMapTool)	ShowMapTool();
	//if (m_bEffectTool) ShowEffectTool();
	//if (m_bCameraTool) ShowCameraTool();
	//if (m_bObjectTool) ShowObjectTool();

	
	//ImGui::End();
	
}

void CImgui_Manager::Render()
{
//  	if (m_StartImgui)
//  	{
//  		ImGui_ImplDX11_NewFrame();
// 		ImGui_ImplWin32_NewFrame();
// 		m_StartImgui = false;
//  		ImGui::NewFrame();
//  	}
// 
// 	// Rendering
// 	ImGui::Render();
// // 	const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
// // 	g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
// // 	g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
// 
// 	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
// 	ImGuiIO& io = ImGui::GetIO(); (void)io;
// 	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
// 	{
// 		ImGui::UpdatePlatformWindows();
// 		ImGui::RenderPlatformWindowsDefault();
// 	}

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
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save"))
			{
				

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
			
			if (ImGui::MenuItem(u8"����"))
			{
				if (m_bMapTool)	ShowMapTool();
			}
			if (ImGui::MenuItem(u8"����Ʈ��"))
			{
				if (m_bEffectTool) ShowEffectTool();
			}
			if (ImGui::MenuItem(u8"������Ʈ��"))
			{
				if (m_bObjectTool) ShowObjectTool();
			}
			if (ImGui::MenuItem(u8"ī�޶���"))
			{
				if (m_bCameraTool) ShowCameraTool();
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

void CImgui_Manager::Toggle_PhysXInfo()
{
}

void CImgui_Manager::Free()
{
	__super::Free();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();


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
	ImGui::Begin(u8"����");
	if (ImGui::BeginTabBar("##MapTabBar"))
	{
		//TODO Ÿ�� �� ����
		if (ImGui::BeginTabItem(u8"Ÿ��"))
		{
			ImGui::Text(u8"Ÿ��");
			ImGui::EndTabItem();
		}
		//TODO Ÿ�� �� ����

		//! ȯ�� �� ����
		if (ImGui::BeginTabItem(u8"ȯ��"))
		{
			ImGui::Text(u8"ȯ��");
			ImGui::EndTabItem();
		}
		//! ȯ�� �� ����

		//! ���� �� ����
		if (ImGui::BeginTabItem(u8"����"))
		{
			ImGui::Text(u8"����");
			ImGui::EndTabItem();
		}
		//! ���� �� ����

		ImGui::EndTabBar();
	}
	ImGui::End();
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
	ImGui::Begin(u8"������Ʈ��");
	if (ImGui::BeginTabBar("##ObjectTabBar"))
	{
		//TODO ������Ʈ1 �� ����
		if (ImGui::BeginTabItem(u8"������Ʈ1"))
		{
			ImGui::Text(u8"������Ʈ1");
			ImGui::EndTabItem();
		}
		//TODO ������Ʈ1 �� ����

		//! ������Ʈ2 �� ����
		if (ImGui::BeginTabItem(u8"������Ʈ2"))
		{
			ImGui::Text(u8"������Ʈ2");
			ImGui::EndTabItem();
		}
		//! ������Ʈ2 �� ����
		ImGui::EndTabBar();
	}
	ImGui::End();
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

