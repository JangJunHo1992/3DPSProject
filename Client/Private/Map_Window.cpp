#include "Map_Window.h"
#include "../../Reference/Imgui/imgui.h"
#include "../../Reference/Imgui/imgui_impl_win32.h"
#include "../../Reference/Imgui/imgui_impl_dx11.h"

#include "Terrain_MapTool.h"
#include "GameInstance.h"
IMPLEMENT_SINGLETON(CMap_Window)

CMap_Window::CMap_Window()
{

}

HRESULT CMap_Window::Initialize()
{
    //���⼭ �ͷ��� ����! 
	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);


	list<CGameObject*> pGameObjects = *(m_pGameInstance->Get_GameObjects(LEVEL_TOOL, TEXT("Layer_BackGround")));

	for (CGameObject* pGameObject : pGameObjects)
	{
		CTerrain_MapTool* pTerrain = dynamic_cast<CTerrain_MapTool*>(pGameObject);
		if (pTerrain)
		{
			m_pTerrain = pTerrain;
			Safe_AddRef(pTerrain);
			break;
		}
	}

	if (m_pTerrain) 
	{
		m_fBrushHeight = m_pTerrain->Get_BrushHeightPoint();
		m_fBrushRange = m_pTerrain->Get_BrushRangePoint();
		m_iMode = m_pTerrain->Get_BrushMode();
	}
	

    return S_OK;
}

void CMap_Window::Start()
{
    //?
}

void CMap_Window::Tick(_float fTimeDelta)
{


    //brush ��� 
}

HRESULT CMap_Window::Render(ID3D11DeviceContext* pDeviceContext)
{
	ImGui::Begin(u8"����");
	if (ImGui::BeginTabBar("##MapTabBar"))
	{
		//TODO Ÿ�� �� ����
		if (ImGui::BeginTabItem(u8"Ÿ��"))
		{
			ImGui::Text(u8"Ÿ��");
			ImGui::InputFloat("TerrainsizeX", &m_TerrainSizeX);
			ImGui::InputFloat("TerrainsizeZ", &m_TerrainSizeZ);
			if (ImGui::Button("Create"))
			{

			}
			ImGui::SliderFloat("BrushHeight", m_fBrushHeight, -10.f, 10.f);
			ImGui::SliderFloat("BrushRange",m_fBrushRange, 0.1f, 30.f);
			ImGui::RadioButton(u8"�����", m_iMode, 0);
			ImGui::SameLine();
			ImGui::RadioButton(u8"����", m_iMode, 1);
			ImGui::SameLine();
			ImGui::RadioButton(u8"�׸�", m_iMode, 2);
			if (ImGui::Button("Save"))
			{
				m_pGameInstance->Save_Json(m_strName, m_MapJson);
			}
			if (ImGui::Button("Load"))
			{

			}

			ImGui::EndTabItem();
		}
		//TODO Ÿ�� �� ����

		//! ȯ�� �� ����
// 		if (ImGui::BeginTabItem(u8"ȯ��"))
// 		{
// 			ImGui::Text(u8"ȯ��");
// 			ImGui::EndTabItem();
// 		}
// 		//! ȯ�� �� ����
// 
// 		//! ���� �� ����
// 		if (ImGui::BeginTabItem(u8"����"))
// 		{
// 			ImGui::Text(u8"����");
// 			ImGui::EndTabItem();
// 		}
		//! ���� �� ����

		ImGui::EndTabBar();
	}
	ImGui::End();
    return S_OK;
}

void CMap_Window::Free()
{
    Safe_Release(m_pGameInstance);
	Safe_Release(m_pTerrain);

}
