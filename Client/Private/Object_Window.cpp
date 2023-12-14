#include "Object_Window.h"
#include "../../Reference/Imgui/imgui.h"
#include "../../Reference/Imgui/imgui_impl_win32.h"
#include "../../Reference/Imgui/imgui_impl_dx11.h"

#include "Terrain_Tool.h"
#include "GameInstance.h"
#include "Level_MapTool.h"

IMPLEMENT_SINGLETON(CObject_Window)

CObject_Window::CObject_Window()
{

}

HRESULT CObject_Window::Initialize()
{
	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	list<CGameObject*>* pGameObjects = (m_pGameInstance->Get_GameObjects(LEVEL_TOOL, TEXT("Layer_BackGround")));

	if (nullptr == pGameObjects)
		return S_OK;

	for (CGameObject* pGameObject : *pGameObjects)
	{
		CTerrain_Tool* pTerrain = dynamic_cast<CTerrain_Tool*>(pGameObject);
		if (pTerrain)
		{
			m_pTerrain = pTerrain;
			Safe_AddRef(pTerrain);
			break;
		}
	}
	//objectList
	m_pGameInstance->Fill_PrototypeTags(&m_vObjectTag);

	 
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
	ImGui::Begin(u8"오브젝트툴");
	if (ImGui::BeginTabBar("##ObjectTabBar"))
	{
		//TODO 오브젝트1 탭 시작
		if (ImGui::BeginTabItem(u8"오브젝트"))
		{
			ImGui::Text(u8"오브젝트");
			
			if (ImGui::TreeNode("ObjectList"))
			{
				
				string items[] = { "Layer_Monster","Layer_Environment","Layer_Object","Layer_Something"};

				static int Object_idx = 0; // Here we store our selection data as an index.
				static int Layer_idx = 0; // Here we store our selection data as an index.
				int ObjectTagSize = m_vObjectTag.size();

				if (ImGui::BeginListBox("ObjectList"))
				{
					for (int n = 0; n < ObjectTagSize; n++)
					{
						const bool is_selected = (Object_idx == n);
						if (ImGui::Selectable(m_vObjectTag[n].c_str(), is_selected))
							Object_idx = n;

						// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
						if (is_selected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndListBox();
				}
				ImGui::Spacing();
				if (ImGui::BeginListBox("LayerList"))
				{
					for (int n = 0; n <4; n++)
					{
						const bool is_selected = (Layer_idx == n);
						if (ImGui::Selectable(items[n].c_str(), is_selected))
							Layer_idx = n;

						// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
						if (is_selected)
						{
							ImGui::SetItemDefaultFocus();
// 							if(m_bCreateCheck)
// 								m_pGameInstance->Add_CloneObject(LEVEL_TOOL,)
						}

					}
					ImGui::EndListBox();
				}
				ImGui::Spacing();
				ImGui::Checkbox("Create",&m_bCreateCheck);
				// Custom size: use all width, 5 items tall
				if (ImGui::BeginListBox("CreateList"))
				{
					for (int n = 0; n < IM_ARRAYSIZE(&ObjectTagSize); n++)
					{
						const bool is_selected = (Object_idx == n);
						if (ImGui::Selectable(m_vObjectTag[n].c_str(), is_selected))
							Object_idx = n;

						// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
						if (is_selected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndListBox();
				}
				if (ImGui::Button("Delete"))
				{

				}
				ImGui::TreePop();
			}

			ImGui::Checkbox(u8"기즈모on/off",&m_bguizmo);
			ImGui::Checkbox("Terrain/Mesh", & m_Terrain_Mesh);
			//여기에 기즈모 넣어 

			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::End();


	return S_OK;
}

void CObject_Window::Set_LevelTool(CLevel_MapTool* _LevelMapTool)
{
	m_pLevel_MapTool = _LevelMapTool;
}

char* CObject_Window::ConverWStringtoC(const wstring& wstr)
{
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);

	char* result = new char[size_needed];

	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, result, size_needed, NULL, NULL);

	return result;
}

void CObject_Window::Free()
{
	Safe_Release(m_pGameInstance);
	Safe_Release(m_pTerrain);
}
