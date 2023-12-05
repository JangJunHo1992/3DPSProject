#include "stdafx.h"
#include "Level_MapTool.h"
#include "GameInstance.h"
#include "Camera_Dynamic.h"
#include "Level_Loading.h"

#include "Imgui_Manager.h"

CLevel_MapTool::CLevel_MapTool(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CLevel(pDevice, pContext)
{
}

HRESULT CLevel_MapTool::Initialize()
{
	
	if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
		return E_FAIL;
	m_pImguiManager = CImgui_Manager::GetInstance();
	Safe_AddRef(m_pImguiManager);

	if (FAILED(m_pImguiManager->SetUp_Imgui(m_pDevice, m_pContext)))
		return E_FAIL;
	
	return S_OK;
}

void CLevel_MapTool::Tick(_float fTimeDelta)
{
	m_pImguiManager->Tick(fTimeDelta);
	if (m_pGameInstance->Get_DIKeyState(DIK_G) & 0x80)
	{
		if (FAILED(m_pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pContext, LEVEL_GAMEPLAY))))
			return;
	}
}

HRESULT CLevel_MapTool::Render()
{
	SetWindowText(g_hWnd, TEXT("게임플레이레벨입니다."));
	m_pImguiManager->Render();

	return S_OK;
}

HRESULT CLevel_MapTool::Ready_Layer_Camera(const wstring& strLayerTag)
{
	CCamera_Dynamic::DYNAMIC_CAMERA_DESC		Desc = {};

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

HRESULT CLevel_MapTool::Ready_Layer_BackGround(const wstring& strLayerTag)
{
	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_TOOL, strLayerTag, TEXT("Prototype_GameObject_Terrain"))))
		return E_FAIL;

	return S_OK;
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

	__super::Free();

}
