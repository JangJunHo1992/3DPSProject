#pragma once
#include "Base.h"
#include "Client_Defines.h"

BEGIN(Client)

class CImgui_Manager final : public CBase
{
	DECLARE_SINGLETON(CImgui_Manager)
private:
	CImgui_Manager() = default;
	virtual	~CImgui_Manager() = default;

public:
	HRESULT SetUp_Imgui(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	void	Tick(_float fTimeDelta);
	void	Render();

	bool CreateDeviceD3D(HWND hWnd);
	void CleanupDeviceD3D();
	void CreateRenderTarget();
	void CleanupRenderTarget();
	LRESULT WINAPI ImGui_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	virtual void Free() override;


private:
	char*	ConvertWCtoC(const wchar_t* str);
	wchar_t* ConvertCtoWC(const char* str);

private:
	_bool				 m_bMainTool = { true };
	_bool				 m_bMapTool, m_bEffectTool, m_bObjectTool, m_bCameraTool = { false };
	_bool				 m_StartImgui = true;

	_bool show_demo_window = true;
	_bool show_another_window = false;
	_bool done = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

private:
	void	HelpMarker(const char* desc);
	char* ConverWStringtoC(const wstring& wstr);

private:
	void	ShowMapTool();
	void	ShowEffectTool();
	void	ShowObjectTool();
	void	ShowCameraTool();
private:
	ID3D11Device* g_pd3dDevice = NULL;
	ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
	IDXGISwapChain* g_pSwapChain = NULL;
	ID3D11RenderTargetView* g_mainRenderTargetView = NULL;
};

END
