#include "stdafx.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>

#include "Imgui_Manager.h"




IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, CImgui_Manager::GetInstance()->ImGui_WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("ImGui Example"), NULL };

IMPLEMENT_SINGLETON(CImgui_Manager)


HRESULT CImgui_Manager::SetUp_Imgui(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	// Create application window
   //ImGui_ImplWin32_EnableDpiAwareness();


	::RegisterClassEx(&wc);
	HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("Dear ImGui DirectX11 Example"), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

	// Initialize Direct3D
	if (!CreateDeviceD3D(hwnd))
	{
		CleanupDeviceD3D();
		::UnregisterClass(wc.lpszClassName, wc.hInstance);
		return 1;
	}

	// Show the window
	::ShowWindow(hwnd, SW_SHOWDEFAULT);
	::UpdateWindow(hwnd);
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	//io.ConfigViewportsNoAutoMerge = true;

	ImGui_ImplWin32_Init(g_hWnd);
	ImGui_ImplDX11_Init(pDevice, pContext);
	//ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
	ImGui::StyleColorsDark();
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\malgun.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesKorean());
	

	return S_OK;
}

void CImgui_Manager::Tick(_float fTimeDelta)
{

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoBackground;

	auto& style = ImGui::GetStyle();
	ImVec4* colors = style.Colors;

	const ImVec4 bgColor = ImVec4(0.1, 0.1, 0.1, 0.5);
	colors[ImGuiCol_WindowBg] = bgColor;
	colors[ImGuiCol_ChildBg] = bgColor;
	colors[ImGuiCol_TitleBg] = bgColor;
	
	MSG msg;
	while(!done)
	{
	while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
			done = true;
	}
 	if (done)
 		break;

	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}

	


	ImGui::Begin(u8"���� ��", &m_bMainTool, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::BeginMenu(u8"��"))
	{
		ImGui::MenuItem(u8"����", NULL, &m_bMapTool);
		ImGui::MenuItem(u8"����Ʈ��", NULL, &m_bEffectTool);
		ImGui::MenuItem(u8"������Ʈ��", NULL, &m_bObjectTool);
		ImGui::MenuItem(u8"ī�޶���", NULL, &m_bCameraTool);

		ImGui::EndMenu();
	}

	if (m_bMapTool)	ShowMapTool();
	if (m_bEffectTool) ShowEffectTool();
	if (m_bCameraTool) ShowCameraTool();
	if (m_bObjectTool) ShowObjectTool();

	
	ImGui::End();
	}
}

void CImgui_Manager::Render()
{
 	if (m_StartImgui)
 	{
 		ImGui_ImplDX11_NewFrame();
 		ImGui_ImplWin32_NewFrame();
 		ImGui::NewFrame();
 		m_StartImgui = false;
 	}

	// Rendering
	ImGui::Render();
	const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
	g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
	g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}

bool CImgui_Manager::CreateDeviceD3D(HWND hWnd)
{
	// Setup swap chain
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	UINT createDeviceFlags = 0;
	//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
		return false;

	CreateRenderTarget();
	return true;
}

void CImgui_Manager::CleanupDeviceD3D()
{
	CleanupRenderTarget();
	if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
	if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
	if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

void CImgui_Manager::CreateRenderTarget()
{
	ID3D11Texture2D* pBackBuffer;
	g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
	pBackBuffer->Release();
}

void CImgui_Manager::CleanupRenderTarget()
{
	if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}

LRESULT __stdcall CImgui_Manager::ImGui_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			CleanupRenderTarget();
			g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
			CreateRenderTarget();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}


void CImgui_Manager::Free()
{
	__super::Free();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	CleanupDeviceD3D();
	::DestroyWindow(g_hWnd);
	::UnregisterClass(wc.lpszClassName, wc.hInstance);
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

