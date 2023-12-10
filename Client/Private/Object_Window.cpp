#include "Object_Window.h"
#include "../../Reference/Imgui/imgui.h"
#include "../../Reference/Imgui/imgui_impl_win32.h"
#include "../../Reference/Imgui/imgui_impl_dx11.h"

#include "Terrain_Tool.h"
#include "GameInstance.h"

IMPLEMENT_SINGLETON(CObject_Window)

CObject_Window::CObject_Window()
{

}

HRESULT CObject_Window::Initialize()
{
	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	return S_OK;
}

void CObject_Window::Start()
{
}

void CObject_Window::Tick(_float fTimeDelta)
{
}

HRESULT CObject_Window::Render(ID3D11DeviceContext* pContext)
{
	ImGui::Begin(u8"������Ʈ��");
	if (ImGui::BeginTabBar("##ObjectTabBar"))
	{
		//TODO ������Ʈ1 �� ����
		if (ImGui::BeginTabItem(u8"������Ʈ1"))
		{
			ImGui::Text(u8"������Ʈ1");
			//ImGui::ListBox("ObjectList");
			ImGui::Button("Create");
			ImGui::SameLine();
			ImGui::Button("Delete");
			//ImGui::ListBox("CreateList");
			ImGui::Checkbox(u8"�����on",&m_bguizmo);
			//���⿡ ����� �־� 

			ImGui::EndTabItem();
		}
	}
	ImGui::End();


	return S_OK;
}

void CObject_Window::Free()
{
}
