#include "stdafx.h"
#include "Level_Logo.h"
#include "GameInstance.h"
#include "BackGround.h"
#include "Level_Loading.h"


CLevel_Logo::CLevel_Logo(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CLevel(pDevice, pContext)
{
}

HRESULT CLevel_Logo::Initialize()
{
	if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
		return E_FAIL;

	return S_OK;
}
//Gameobject map에서 Object_Window로 가져오기
void CLevel_Logo::Tick(_float fTimeDelta)
{
	if (m_pGameInstance->Get_DIKeyState(DIK_SPACE) & 0x80)
	{
		if (FAILED(m_pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pContext, LEVEL_GAMEPLAY))))
			return;
	}
	else if (m_pGameInstance->Get_DIKeyState(DIK_M) & 0x80)
	{
		if (FAILED(m_pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pContext, LEVEL_TOOL))))
			return;
	}
	
}

HRESULT CLevel_Logo::Render()
{
	SetWindowText(g_hWnd, TEXT("로고레벨입니다."));

	return S_OK;
}

HRESULT CLevel_Logo::Ready_Layer_BackGround(const wstring & strLayerTag)
{
	CBackGround::BACKGROUND_DESC		BackGroundDesc = {};

	BackGroundDesc.fX = g_iWinSizeX >> 1;
	BackGroundDesc.fY = g_iWinSizeY >> 1;
	BackGroundDesc.fSizeX = g_iWinSizeX;
	BackGroundDesc.fSizeY = g_iWinSizeY;
	BackGroundDesc.fRotationPerSec = XMConvertToRadians(90.f);
	BackGroundDesc.fSpeedPerSec = 10.f;

	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_LOGO, strLayerTag, TEXT("Prototype_GameObject_BackGround"), &BackGroundDesc)))
		return E_FAIL;

	return S_OK;
}

CLevel_Logo * CLevel_Logo::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
{
	CLevel_Logo*		pInstance = new CLevel_Logo(pDevice, pContext);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_Logo");
		Safe_Release(pInstance);
	}
	return pInstance; 
}

void CLevel_Logo::Free()
{
	__super::Free();

}
