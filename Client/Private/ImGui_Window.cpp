#include "stdafx.h"
#include "../../Reference/Imgui/imgui.h"
#include "../../Reference/Imgui/imgui_impl_win32.h"
#include "../../Reference/Imgui/imgui_impl_dx11.h"
#include "ImGui_Window.h"


CImGui_Window::CImGui_Window()
{
}

void CImGui_Window::Tick(_float fTimeDelta)
{
	m_fTimeDelta = fTimeDelta;
}

HRESULT CImGui_Window::Begin()
{
	ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(1.f, 1.f, 1.f, 1.f));

	ImGui::SetNextWindowSize(ImVec2(0.f,0.f), 0);

	if (!(ImGui::Begin(m_strImGuiName.c_str(), 0, ImGuiWindowFlags_None)))
		return S_OK;

	return S_OK;
}

HRESULT CImGui_Window::End()
{
	ImGui::PopStyleColor();

	ImGui::End();

	return S_OK;
}

void CImGui_Window::Free()
{
}
