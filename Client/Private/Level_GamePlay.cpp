#include "stdafx.h"
#include "Level_GamePlay.h"
#include "GameInstance.h"
#include "Camera_Dynamic.h"
#include "Level_Loading.h"
#include "Monster.h"
#include "Player.h"
#include "King.h"
#include "DarkKnight.h"
#include "Wizard.h"

CLevel_GamePlay::CLevel_GamePlay(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CLevel(pDevice, pContext)
{
}

HRESULT CLevel_GamePlay::Initialize()
{
	if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
		return E_FAIL;

 	if (FAILED(Ready_Layer_Player(TEXT("Layer_Player"))))
 		return E_FAIL;

	if (FAILED(Ready_Layer_Monster(TEXT("Layer_Monster"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
		return E_FAIL;

	return S_OK;
}

void CLevel_GamePlay::Tick(_float fTimeDelta)
{
	if (m_pGameInstance->Get_DIKeyState(DIK_M) & 0x80)
	{
		if (FAILED(m_pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pContext, LEVEL_TOOL))))
			return;
	}

	list<CGameObject*>* pPlayers = m_pGameInstance->Get_GameObjects(LEVEL_GAMEPLAY, TEXT("Layer_Player"));

	if (m_pGameInstance->Key_Down(DIK_SPACE))
	{
		for (CGameObject* pGameObject : *pPlayers)
		{
			CCharacter* pCharacter = dynamic_cast<CCharacter*>(pGameObject);
			if (pCharacter)
			{
				_uint iNumAnimations = pCharacter->Get_NumAnimations();
				_uint iAnimIndex = pCharacter->Get_CurrentAnimIndex() + 1;
				if (iAnimIndex >= iNumAnimations - 1)
				{
					iAnimIndex = 0;
				}
				pCharacter->Set_Animation(iAnimIndex, CModel::ANIM_STATE::ANIM_STATE_NORMAL, true);

			}

		}
	}


	//if (m_pGameInstance->Key_Down(DIK_V))
	//{
	//	for (CGameObject* pGameObject : *pMonsters)
	//	{
	//		CMonster* pMonster = dynamic_cast<CMonster*>(pGameObject);
	//		if (pMonster)
	//		{
	//			_uint iAnimIndex = pMonster->Get_CurrentAnimIndex();
	//			pMonster->Set_Animation(iAnimIndex, CModel::ANIM_STATE::ANIM_STATE_NORMAL, true);
	//		}

	//	}
	//}

	//if (m_pGameInstance->Key_Down(DIK_B))
	//{
	//	for (CGameObject* pGameObject : *pMonsters)
	//	{
	//		CMonster* pMonster = dynamic_cast<CMonster*>(pGameObject);
	//		if (pMonster)
	//		{
	//			_uint iAnimIndex = pMonster->Get_CurrentAnimIndex();
	//			pMonster->Set_Animation(iAnimIndex, CModel::ANIM_STATE::ANIM_STATE_STOP, true);
	//		}

	//	}
	//}

	//if (m_pGameInstance->Key_Down(DIK_N))
	//{
	//	for (CGameObject* pGameObject : *pMonsters)
	//	{
	//		CMonster* pMonster = dynamic_cast<CMonster*>(pGameObject);
	//		if (pMonster)
	//		{
	//			_uint iAnimIndex = pMonster->Get_CurrentAnimIndex();
	//			pMonster->Set_Animation(iAnimIndex, CModel::ANIM_STATE::ANIM_STATE_REVERSE, true);
	//		}
	//	}
	//}
}

HRESULT CLevel_GamePlay::Render()
{
	SetWindowText(g_hWnd, TEXT("게임플레이레벨입니다."));
	
	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Camera(const wstring& strLayerTag)
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

	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Camera_Dynamic"), &Desc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Player(const wstring& strLayerTag)
{
	//if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Player_GamePlay"))))
	//	return E_FAIL;

	//if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Raider_GamePlay"))))
	// 	return E_FAIL;

	//if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_King_GamePlay"), &PlayerDesc)))
	//	return E_FAIL;

	//if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_DarkKnight_GamePlay"), &PlayerDesc)))
	//	return E_FAIL;

	//if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_KnightGuard_GamePlay"), &PlayerDesc)))
	//	return E_FAIL;

	//if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Golem_GamePlay"), &PlayerDesc)))
	//	return E_FAIL;

	//if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Wizard_GamePlay"), &PlayerDesc)))
	//	return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Monster(const wstring& strLayerTag)
{
	for (size_t i = 0; i < 20; i++)
	{
		if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Monster_GamePlay"))))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_BackGround(const wstring& strLayerTag)
{
	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Terrain_GamePlay"))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Sky"))))
		return E_FAIL;

	//if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_ForkLift_GamePlay"))))
	//	return E_FAIL;

	return S_OK;

}

CLevel_GamePlay * CLevel_GamePlay::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
{
	CLevel_GamePlay*		pInstance = new CLevel_GamePlay(pDevice, pContext);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance; 
}

void CLevel_GamePlay::Free()
{
	__super::Free();

}
