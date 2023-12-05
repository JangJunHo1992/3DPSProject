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
	

	//ImGui::Begin(u8"메인 툴", &m_bMainTool, ImGuiWindowFlags_AlwaysAutoResize);

	//if (ImGui::BeginMenu(u8"툴"))
	//{
	//	ImGui::MenuItem(u8"맵툴", NULL, &m_bMapTool);
	//	ImGui::MenuItem(u8"이펙트툴", NULL, &m_bEffectTool);
	//	ImGui::MenuItem(u8"오브젝트툴", NULL, &m_bObjectTool);
	//	ImGui::MenuItem(u8"카메라툴", NULL, &m_bCameraTool);

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
			//추후에 Level 생기면 여기에 넣어서 볼수 있게 ㄱㄱ 



			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Editer"))
		{
			
			if (ImGui::MenuItem(u8"맵툴"))
			{
				if (m_bMapTool)	ShowMapTool();
			}
			if (ImGui::MenuItem(u8"이펙트툴"))
			{
				if (m_bEffectTool) ShowEffectTool();
			}
			if (ImGui::MenuItem(u8"오브젝트툴"))
			{
				if (m_bObjectTool) ShowObjectTool();
			}
			if (ImGui::MenuItem(u8"카메라툴"))
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
	//반환할 char* 변수 선언
	char* pStr;
	//입력받은 wchar_t 변수의 길이를 구함
	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	//char* 메모리 할당
	pStr = new char[strSize];
	//형 변환
	WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);
	return pStr;
}

wchar_t* CImgui_Manager::ConvertCtoWC(const char* str)
{
	//wchar_t형 변수 선언
	wchar_t* pStr;
	//멀티 바이트 크기 계산 길이 반환
	int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);
	//wchar_t 메모리 할당
	pStr = new WCHAR[strSize];
	//형 변환
	MultiByteToWideChar(CP_ACP, 0, str, (int)strlen(str) + 1, pStr, strSize);
	return pStr;
}



void CImgui_Manager::ShowMapTool()
{
	ImGui::Begin(u8"맵툴");
	if (ImGui::BeginTabBar("##MapTabBar"))
	{
		//TODO 타일 탭 시작
		if (ImGui::BeginTabItem(u8"타일"))
		{
			ImGui::Text(u8"타일");
			ImGui::EndTabItem();
		}
		//TODO 타일 탭 종료

		//! 환경 탭 시작
		if (ImGui::BeginTabItem(u8"환경"))
		{
			ImGui::Text(u8"환경");
			ImGui::EndTabItem();
		}
		//! 환경 탭 종료

		//! 높이 탭 시작
		if (ImGui::BeginTabItem(u8"높이"))
		{
			ImGui::Text(u8"높이");
			ImGui::EndTabItem();
		}
		//! 높이 탭 종료

		ImGui::EndTabBar();
	}
	ImGui::End();
}



void CImgui_Manager::ShowEffectTool()
{
	ImGui::Begin(u8"이펙트툴");
	if (ImGui::BeginTabBar("##EffectTabBar"))
	{
		//TODO 이펙트 탭 시작
		if (ImGui::BeginTabItem(u8"이펙트"))
		{
			ImGui::Text(u8"이펙트");
			ImGui::EndTabItem();
		}
		//TODO 이펙트 탭 종료

		//! 파티클 탭 시작
		if (ImGui::BeginTabItem(u8"파티클"))
		{
			ImGui::Text(u8"파티클");
			ImGui::EndTabItem();
		}
		//! 파티클 탭 종료
		ImGui::EndTabBar();
	}
	ImGui::End();
}

void CImgui_Manager::ShowObjectTool()
{
	ImGui::Begin(u8"오브젝트툴");
	if (ImGui::BeginTabBar("##ObjectTabBar"))
	{
		//TODO 오브젝트1 탭 시작
		if (ImGui::BeginTabItem(u8"오브젝트1"))
		{
			ImGui::Text(u8"오브젝트1");
			ImGui::EndTabItem();
		}
		//TODO 오브젝트1 탭 종료

		//! 오브젝트2 탭 시작
		if (ImGui::BeginTabItem(u8"오브젝트2"))
		{
			ImGui::Text(u8"오브젝트2");
			ImGui::EndTabItem();
		}
		//! 오브젝트2 탭 종료
		ImGui::EndTabBar();
	}
	ImGui::End();
}

void CImgui_Manager::ShowCameraTool()
{
	ImGui::Begin(u8"카메라툴");
	if (ImGui::BeginTabBar("##CameraTabBar"))
	{
		//TODO 베지어 탭 시작
		if (ImGui::BeginTabItem(u8"베지어"))
		{
			ImGui::Text(u8"베지어");
			ImGui::EndTabItem();
		}
		//TODO 베지어 탭 종료

		//! 메뉴얼 탭 시작
		if (ImGui::BeginTabItem(u8"메뉴얼"))
		{
			ImGui::Text(u8"메뉴얼");
			ImGui::EndTabItem();
		}
		//! 메뉴얼 탭 종료
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

