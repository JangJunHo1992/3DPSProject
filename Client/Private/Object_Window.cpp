#include "Object_Window.h"
#include "../../Reference/Imgui/imgui.h"
#include "../../Reference/Imgui/imgui_impl_win32.h"
#include "../../Reference/Imgui/imgui_impl_dx11.h"

#include "Terrain_Tool.h"
#include "GameInstance.h"
#include "Level_MapTool.h"
#include "GameObject.h"

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
	m_pGameInstance->Get_CloneGameObjects(LEVEL_TOOL, &m_CreateList);

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
							if (m_bCreateCheck)
								if (m_pGameInstance->Mouse_Down(DIM_LB))
								{
									Create_Object(ConvertCtoWC(items[Layer_idx].c_str()), ConvertCtoWC(m_vObjectTag[Object_idx].c_str()));

									m_bCloneCount = true;
									m_bListCheck = true;
								}
							
						}

					}
					
					ImGui::EndListBox();
				}
				ImGui::Spacing();
				ImGui::Checkbox("Create",&m_bCreateCheck);
				ImGui::Checkbox("Delete",& m_bDeleteCheck);
				

				
				static int CreateIndex = 0; // Here we store our selection data as an index.
				
				if (m_bListCheck)
				{
					m_iCreateObjectSize =m_CreateList.size();
					if (ImGui::BeginListBox("CreateList"))
					{

						for (int n = 0; n < m_iCreateObjectSize; n++)
						{
							string str ="Object";
							string str2 = to_string(n);

							const bool is_selected = (CreateIndex == n);
							if (ImGui::Selectable((str + "." + str2).c_str(), is_selected))
								CreateIndex = n;

							// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
							if (is_selected)
							{
								ImGui::SetItemDefaultFocus();
								if (m_bDeleteCheck)
								{
									_bool isdead = true;
									m_CreateList[CreateIndex]->Set_isdead(isdead);
									m_CreateList.erase(m_CreateList.begin() + CreateIndex);
									m_bDeleteCheck = false;
								}
									
							}
						}
						ImGui::EndListBox();
					}
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
	if (m_bCloneCount)
	{
		m_CreateList.clear();
		m_pGameInstance->Get_CloneGameObjects(LEVEL_TOOL, &m_CreateList);

		m_bCloneCount = false;
	}


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
char* CObject_Window::ConvertWCtoC(const wchar_t* str)
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

wchar_t* CObject_Window::ConvertCtoWC(const char* str)
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

void CObject_Window::Create_Object(const wstring& strLayerTag, const wstring& strPrototypeTag)
{
	m_pGameInstance->Add_CloneObject(LEVEL_TOOL, strLayerTag, strPrototypeTag);

	list<CGameObject*> pGameObjects = *(m_pGameInstance->Get_GameObjects(LEVEL_TOOL, strLayerTag));
	CGameObject* pGameObject = pGameObjects.back();

	const _float3& temp = m_pTerrain->Get_PickedPosFloat3();
	pGameObject->Set_Position(temp);

}

void CObject_Window::Free()
{
	Safe_Release(m_pGameInstance);
	Safe_Release(m_pTerrain);
	for (auto& CloneCount : m_CreateList)
	{
		Safe_Release(CloneCount);
	}
}
