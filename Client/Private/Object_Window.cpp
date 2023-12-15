#include "Object_Window.h"
#include "../../Reference/Imgui/imgui.h"
#include "../../Reference/Imgui/imgui_impl_win32.h"
#include "../../Reference/Imgui/imgui_impl_dx11.h"
#include "../../Reference/Imgui/ImGuizmo/ImGuizmo.h"
#include "../../Reference/Imgui/ImGuizmo/ImSequencer.h"
#include "../../Reference/Imgui/ImGuizmo/ImZoomSlider.h"
#include "../../Reference/Imgui/ImGuizmo/ImCurveEdit.h"
#include "../../Reference/Imgui/ImGuizmo/GraphEditor.h"

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

	//guizmo


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
	Check_ImGui_Rect();
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
								m_PickingObject = m_CreateList[CreateIndex];
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
			if (m_bguizmo)
				Compress_Guizmo_Mode();
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
void CObject_Window::Compress_Guizmo_Mode()
{
	if (nullptr == m_PickingObject)
		return;

	ImGuizmo_Initialize();
	Set_GuizmoCamProj();
	Set_GuizmoCamView();
	Setup_Guizmo();

// 	if (Picking_Model())
// 		int a = 0;
}
#pragma region Guizmo

void CObject_Window::Setup_Guizmo()
{
	/*==== Set ImGuizmo ====*/
	ImGuizmo::SetOrthographic(false);
	ImGuiIO& io = ImGui::GetIO();
	ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);

	if (ImGui::IsKeyPressed(ImGuiKey_T))
		mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	if (ImGui::IsKeyPressed(ImGuiKey_R))
		mCurrentGizmoOperation = ImGuizmo::ROTATE;
	if (ImGui::IsKeyPressed(ImGuiKey_E))
		mCurrentGizmoOperation = ImGuizmo::SCALE;

	if (ImGui::RadioButton("Translate", mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
		mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	ImGui::SameLine();
	if (ImGui::RadioButton("Rotate", mCurrentGizmoOperation == ImGuizmo::ROTATE))
		mCurrentGizmoOperation = ImGuizmo::ROTATE;
	ImGui::SameLine();
	if (ImGui::RadioButton("Scale", mCurrentGizmoOperation == ImGuizmo::SCALE))
		mCurrentGizmoOperation = ImGuizmo::SCALE;

	_float* arrView = m_arrView;
	_float* arrProj = m_arrProj;

	__float4x4 matWorld = m_PickingObject->Get_TransformComp()->Get_WorldFloat4x4();
	_float arrWorld[] = { matWorld._11,matWorld._12,matWorld._13,matWorld._14,
				 matWorld._21,matWorld._22,matWorld._23,matWorld._24,
				 matWorld._31,matWorld._32,matWorld._33,matWorld._34,
				 matWorld._41,matWorld._42,matWorld._43,matWorld._44 };

	float matrixTranslation[3], matrixRotation[3], matrixScale[3];
	ImGuizmo::DecomposeMatrixToComponents(arrWorld, matrixTranslation, matrixRotation, matrixScale);
	ImGui::DragFloat3("Tr", matrixTranslation);
	ImGui::DragFloat3("Rt", matrixRotation);
	ImGui::DragFloat3("Sc", matrixScale);
	ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, arrWorld);


	ImGui::Checkbox("UseSnap", &useSnap);
	ImGui::SameLine();

	switch (mCurrentGizmoOperation)
	{
	case ImGuizmo::TRANSLATE:
		ImGui::DragFloat3("Snap", &snap[0]);
		break;
	case ImGuizmo::ROTATE:
		ImGui::DragFloat3("Angle Snap", &snap[0]);
		break;
	case ImGuizmo::SCALE:
		ImGui::DragFloat3("Scale Snap", &snap[0]);
		break;
	}

	ImGuizmo::Manipulate(arrView, arrProj, mCurrentGizmoOperation, mCurrentGizmoMode, arrWorld, NULL, useSnap ? &snap[0] : NULL);


	__float4x4 matW = { arrWorld[0],arrWorld[1],arrWorld[2],arrWorld[3],
			 arrWorld[4],arrWorld[5],arrWorld[6],arrWorld[7],
			 arrWorld[8],arrWorld[9],arrWorld[10],arrWorld[11],
			 arrWorld[12],arrWorld[13],arrWorld[14],arrWorld[15] };
	

	m_PickingObject->Get_TransformComp()->Set_WorldMatrix(matW);

	if (ImGuizmo::IsOver())
	{
		int a = 0;
	}
}

void CObject_Window::ImGuizmo_Initialize()
{
	/*기즈모 뷰, 투영 멤버변수 메모리 할당
	* SetUp 에서 쓰는 Guizmo가 float* [] 이므로 배열로 만들어야함
	* = 동적배열 */
	m_arrView = new _float[16];
	m_arrProj = new _float[16];
}

void CObject_Window::Set_GuizmoCamProj()
{
	_float4x4 matCamProj = m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_PROJ);

	_float     arrProj[] = { matCamProj._11,matCamProj._12,matCamProj._13,matCamProj._14,
						 matCamProj._21,matCamProj._22,matCamProj._23,matCamProj._24,
						 matCamProj._31,matCamProj._32,matCamProj._33,matCamProj._34,
						 matCamProj._41,matCamProj._42,matCamProj._43,matCamProj._44 };
	memcpy(m_arrProj, &arrProj, sizeof(arrProj));
}

void CObject_Window::Set_GuizmoCamView()
{
	_float4x4 matCamView = m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_VIEW);

	_float     arrView[] = { matCamView._11,matCamView._12,matCamView._13,matCamView._14,
				 matCamView._21,matCamView._22,matCamView._23,matCamView._24,
				 matCamView._31,matCamView._32,matCamView._33,matCamView._34,
				 matCamView._41,matCamView._42,matCamView._43,matCamView._44 };

	memcpy(m_arrView, &arrView, sizeof(arrView));
}

#pragma endregion
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

_bool CObject_Window::Check_ImGui_Rect()
{
	POINT tMouse = {};
	GetCursorPos(&tMouse);
	ScreenToClient(m_pGameInstance->Get_GraphicDesc().hWnd, &tMouse);

	ImVec2 windowPos = ImGui::GetWindowPos(); //왼쪽상단모서리점
	ImVec2 windowSize = ImGui::GetWindowSize();

	if (tMouse.x >= windowPos.x && tMouse.x <= windowPos.x + windowSize.x &&
		tMouse.y >= windowPos.y && tMouse.y <= windowPos.y + windowSize.y)
	{
		return false; //ImGui 영역 내
	}
	return true; //ImGui 영역이랑 안 겹침!
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
