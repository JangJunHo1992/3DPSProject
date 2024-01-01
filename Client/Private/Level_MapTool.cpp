#include "stdafx.h"
#include "Level_MapTool.h"
#include "GameInstance.h"
#include "Camera_Dynamic.h"
#include "Camera_Dynamic_Tool.h"
#include "Level_Loading.h"
#include "GameObject.h"
#include "Imgui_Manager.h"

#include "Object_Window.h"
#include "Terrain_Tool.h"
#include "MapTool_State_Terrain.h"
#include "RapidJson.h"
#include "Model_Tool.h"
#include "Terrain_Tool.h"


CLevel_MapTool::CLevel_MapTool(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CLevel(pDevice, pContext)
{
	m_pDevice = pDevice;
	m_pContext = pContext;

	Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pContext);
}

HRESULT CLevel_MapTool::Initialize()
{
	if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Monster(TEXT("Layer_Monster"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
		return E_FAIL;

	

	m_pImguiManager = CImgui_Manager::GetInstance();
	Safe_AddRef(m_pImguiManager);

	m_pObjectWin = CObject_Window::GetInstance();
	Safe_AddRef(m_pObjectWin);
	
	if (FAILED(m_pImguiManager->SetUp_Imgui(m_pDevice, m_pContext)))
		return E_FAIL;

	m_pActor = new CActor<CLevel_MapTool>(this);
	m_pActor->Set_State(new CMapTool_State_Terrain());

	m_pObjectWin->Set_LevelTool(this);

	return S_OK;
}

void CLevel_MapTool::Tick(_float fTimeDelta)
{
	if (m_pGameInstance->Key_Down(DIK_TAB))
		m_bStop = !m_bStop;
		
	if (m_bStop)
		return;

	if (nullptr == m_pTerrain) 
	{
		list<CGameObject*>* pGameObjects = (m_pGameInstance->Get_GameObjects(LEVEL_TOOL, TEXT("Layer_BackGround")));

		if (nullptr != pGameObjects) 
		{
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
		}
	}


	if (m_pGameInstance->Key_Down(DIK_J)) 
	{
		m_pGameInstance->Save_Objects_With_Json(LEVEL_TOOL, "Save_GameObjects.json");
	}
	

	m_pImguiManager->Tick(fTimeDelta);
	if (m_pGameInstance->Key_Down(DIK_G))
	{
		if (FAILED(m_pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pContext, LEVEL_GAMEPLAY))))
			return;
	}

	m_pActor->Update_State(fTimeDelta);

}

HRESULT CLevel_MapTool::Render()
{
	SetWindowText(g_hWnd, TEXT("툴레벨입니다."));
	m_pImguiManager->Render();

	return S_OK;
}

void CLevel_MapTool::Update_MousePos()
{
	if (nullptr == m_pTerrain)
		return;

	m_pTerrain->Update_MousePos();
}

void CLevel_MapTool::Terrain_Pick()
{
	if (m_pGameInstance->Get_DIMouseState(DIM_LB))
	{
		if (nullptr == m_pTerrain)
			return;

		m_pTerrain->pick();
	}
}

void CLevel_MapTool::Create_Object(const wstring& strLayerTag, const wstring& strPrototypeTag)
{
	m_pGameInstance->Add_CloneObject(LEVEL_TOOL, strLayerTag, strPrototypeTag);
	
	list<CGameObject*> pGameObjects = *(m_pGameInstance->Get_GameObjects(LEVEL_TOOL, strLayerTag));
	CGameObject* pGameObject = pGameObjects.back();
	
	const _float3& temp = m_pTerrain->Get_PickedPosFloat3();
	pGameObject->Set_Position(temp);

	//const _float3 & vState
}

void CLevel_MapTool::Create_Raider()
{
	Create_Object(TEXT("Layer_Monster"), TEXT("Prototype_GameObject_Raider"));
}

void CLevel_MapTool::Resize_Plane(_ushort x, _ushort z)
{
	if (m_pTerrain->IsPlane()) 
	{
		//m_pTerrain.
	}
}

CGameObject* CLevel_MapTool::Select_Object(const wstring& strLayerTag)
{
	list<CGameObject*> pGameObjects = *(m_pGameInstance->Get_GameObjects(LEVEL_TOOL, strLayerTag));

	for (CGameObject* pGameObject : pGameObjects)
	{
		_float3 vPos;
		if (pGameObject->Pick(&vPos))
		{
			return pGameObject;
		}
	}

	return nullptr;
}

void CLevel_MapTool::Delete_Object(CGameObject* pGameObject)
{
}






HRESULT CLevel_MapTool::Ready_Layer_Camera(const wstring& strLayerTag)
{
	CCamera_Dynamic_Tool::DYNAMIC_CAMERA_DESC		Desc = {};

	Desc.fMouseSensor = 0.05f;
	Desc.vEye = _float4(0.f, 20.f, -15.f, 1.f);
	Desc.vAt = _float4(0.f, 0.f, 0.f, 1.f);
	Desc.fFovy = XMConvertToRadians(60.0f);
	Desc.fAspect = (_float)g_iWinSizeX / g_iWinSizeY;
	Desc.fNear = 0.1f;
	Desc.fFar = 1000.f;
	Desc.fSpeedPerSec = 20.f;
	Desc.fRotationPerSec = XMConvertToRadians(180.0f);

	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_TOOL, strLayerTag, TEXT("Prototype_GameObject_Camera_Dynamic"), &Desc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_MapTool::Ready_Layer_Monster(const wstring& strLayerTag)
{
	//if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_TOOL, strLayerTag, TEXT("Prototype_GameObject_Raider_Tool"))))
	//	return E_FAIL;

	return S_OK;
}

HRESULT CLevel_MapTool::Ready_Layer_BackGround(const wstring& strLayerTag)
{
	//if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_TOOL, strLayerTag, TEXT("Prototype_GameObject_Terrain_Tool"))))
	//	return E_FAIL;

	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_TOOL, strLayerTag, TEXT("Prototype_GameObject_Plane"))))
		return E_FAIL;

	return S_OK;
}

void CLevel_MapTool::Set_BrushRange(_float _fBrushRange)
{
	if (nullptr == m_pTerrain)
		return;

	m_pTerrain->Set_BrushRange(_fBrushRange); 
}

CLevel_MapTool * CLevel_MapTool::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
{
	CLevel_MapTool*		pInstance = new CLevel_MapTool(pDevice, pContext);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_MapTool");
		Safe_Release(pInstance);
	}
	return pInstance; 
}

void CLevel_MapTool::Free()
{
	Safe_Release(m_pImguiManager);
	Safe_Release(m_pObjectWin);

	Safe_Delete(m_pActor);
	//m_pActor->Free();

	Safe_Release(m_pTerrain);

	Safe_Release(m_pDevice);
	Safe_Release(m_pContext);

	__super::Free();

}
