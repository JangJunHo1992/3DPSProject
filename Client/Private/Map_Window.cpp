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
    //여기서 터레인 생성! 
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


    //brush 사용 
}

HRESULT CMap_Window::Render(ID3D11DeviceContext* pDeviceContext)
{
	ImGui::Begin(u8"맵툴");
	if (ImGui::BeginTabBar("##MapTabBar"))
	{
		//TODO 타일 탭 시작
		if (ImGui::BeginTabItem(u8"타일"))
		{
			ImGui::Text(u8"타일");
			ImGui::InputFloat("TerrainsizeX", &m_TerrainSizeX);
			ImGui::InputFloat("TerrainsizeZ", &m_TerrainSizeZ);
			if (ImGui::Button("Create"))
			{

			}
			ImGui::SliderFloat("BrushHeight", m_fBrushHeight, -10.f, 10.f);
			ImGui::SliderFloat("BrushRange",m_fBrushRange, 0.1f, 30.f);
			ImGui::RadioButton(u8"원기둥", m_iMode, 0);
			ImGui::SameLine();
			ImGui::RadioButton(u8"원형", m_iMode, 1);
			ImGui::SameLine();
			ImGui::RadioButton(u8"네모", m_iMode, 2);
			if (ImGui::Button("Save"))
			{
				m_pGameInstance->Save_Json(m_strName, m_MapJson);
			}
			if (ImGui::Button("Load"))
			{

			}

			ImGui::EndTabItem();
		}
		//TODO 타일 탭 종료

		//! 환경 탭 시작
// 		if (ImGui::BeginTabItem(u8"환경"))
// 		{
// 			ImGui::Text(u8"환경");
// 			ImGui::EndTabItem();
// 		}
// 		//! 환경 탭 종료
// 
// 		//! 높이 탭 시작
// 		if (ImGui::BeginTabItem(u8"높이"))
// 		{
// 			ImGui::Text(u8"높이");
// 			ImGui::EndTabItem();
// 		}
		//! 높이 탭 종료

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
