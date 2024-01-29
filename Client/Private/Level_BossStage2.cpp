#include "stdafx.h"
#include "Level_BossStage2.h"
#include "GameInstance.h"
#include "Camera_Dynamic.h"
#include "Level_Loading.h"
#include "Monster.h"
#include "Player.h"
#include "Light.h"


CLevel_BossStage2::CLevel_BossStage2(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CLevel(pDevice, pContext)
{
}

HRESULT CLevel_BossStage2::Initialize()
{
	Load_Objects_With_Json("Save_GameObjects3.json");

	if (FAILED(Ready_Layer_Player(TEXT("Layer_Player"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Monster(TEXT("Layer_Monster"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Effect(TEXT("Layer_Effect"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
		return E_FAIL;
	list<CGameObject*>* playerList = m_pGameInstance->Get_GameObjects(LEVEL_BOSS2, TEXT("Layer_Player"));
	pPlayer = dynamic_cast<CCharacter*>((*playerList).back());
	m_pGameInstance->Set_Player(pPlayer);

	_vector vPos = pPlayer->Get_TransformComp()->Get_State(CTransform::STATE::STATE_POSITION);
	pPlayer->Get_Navigation()->Reset_CurrentIndex(vPos);

	list<CGameObject*>* monsterList = m_pGameInstance->Get_GameObjects(LEVEL_BOSS2, TEXT("Layer_Monster"));

	if (monsterList)
	{
		for (auto& pGameObject : *monsterList)
		{
			CCharacter* pMonster = dynamic_cast<CCharacter*>(pGameObject);
			if (pMonster)
			{
				_vector vPos = pMonster->Get_TransformComp()->Get_State(CTransform::STATE::STATE_POSITION);
				pMonster->Get_Navigation()->Reset_CurrentIndex(vPos);
			}
		}
	}
	if (FAILED(Ready_LightDesc()))
		return E_FAIL;
	return S_OK;
}

void CLevel_BossStage2::Tick(_float fTimeDelta)
{

}

HRESULT CLevel_BossStage2::Render()
{
	SetWindowText(g_hWnd, TEXT("BossStage2."));

	return S_OK;
}

HRESULT CLevel_BossStage2::Ready_LightDesc()
{
	LIGHT_DESC			LightDesc{};

	LightDesc.eType = LIGHT_DESC::TYPE_DIRECTIONAL;
	LightDesc.vDirection = _float4(1.f, -1.f, 1.f, 0.f);
	LightDesc.vDiffuse = _float4(0.6f, 0.6f, 0.6f, 1.f);
	LightDesc.vAmbient = _float4(0.2f, 0.2f, 0.2f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.f, 1.f, 1.f);

	if (FAILED(m_pGameInstance->Add_Light(LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof LightDesc);

	LightDesc.eType = LIGHT_DESC::TYPE_POINT;
	LightDesc.vPosition = _float4(30.f, 3.f, 30.f, 1.f);
	LightDesc.fRange = 20.f;
	LightDesc.vDiffuse = _float4(1.f, 0.0f, 0.0f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.1f, 0.1f, 1.f);
	LightDesc.vSpecular = LightDesc.vDiffuse;

	if (FAILED(m_pGameInstance->Add_Light(LightDesc)))
		return E_FAIL;

	LightDesc.eType = LIGHT_DESC::TYPE_POINT;
	LightDesc.vPosition = _float4(50.f, 3.f, 30.f, 1.f);
	LightDesc.fRange = 20.f;
	LightDesc.vDiffuse = _float4(0.0f, 1.f, 0.0f, 1.f);
	LightDesc.vAmbient = _float4(0.1f, 0.4f, 0.1f, 1.f);
	LightDesc.vSpecular = LightDesc.vDiffuse;

	if (FAILED(m_pGameInstance->Add_Light(LightDesc)))
		return E_FAIL;

// 	if (FAILED(m_pGameInstance->Add_Light(LightDesc)))
// 		return E_FAIL;

	LightDesc.eType = LIGHT_DESC::TYPE_POINT;
	LightDesc.vPosition = _float4(70.f, 10.f, 30.f, 1.f);
	LightDesc.fRange = 20.f;
	LightDesc.vDiffuse = _float4(1.f, 0.0f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.1f, 0.4f, 1.f);
	LightDesc.vSpecular = LightDesc.vDiffuse;

	if (FAILED(m_pGameInstance->Add_Light(LightDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_BossStage2::Ready_Layer_Camera(const wstring& strLayerTag)
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

	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_BOSS2, strLayerTag, TEXT("Prototype_GameObject_Camera_Dynamic"), &Desc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_BossStage2::Ready_Layer_Player(const wstring& strLayerTag)
{
	//if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Player"))))
	//	return E_FAIL;

// 	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_BOSS2, strLayerTag, TEXT("Prototype_GameObject_Covus"))))
// 		return E_FAIL;

// 	list<CGameObject*> m_pPlayerLayer = *m_pGameInstance->Get_GameObjects(LEVEL_BOSS2, strLayerTag);
// 
// 	CGameObject* pPlayer = m_pPlayerLayer.back();
// 
// 	m_pGameInstance->Set_Player(pPlayer);

	return S_OK;
}

HRESULT CLevel_BossStage2::Ready_Layer_Monster(const wstring& strLayerTag)
{

// 	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Monster"))))
// 		return E_FAIL;
// 	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_BOSS2, strLayerTag, TEXT("Prototype_GameObject_Magician"))))
// 		return E_FAIL;
// 	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Varg"))))
// 		return E_FAIL;
// 	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_JobMob1"))))
// 		return E_FAIL;
// 	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_JobMob2"))))
// 		return E_FAIL;

	return S_OK;
}
HRESULT CLevel_BossStage2::Ready_Layer_Effect(const wstring& strLayerTag)
{
// 	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Particle_Blue"))))
// 		return E_FAIL;

	// 	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Particle_Red"))))
	// 		return E_FAIL;

	return S_OK;
}
HRESULT CLevel_BossStage2::Ready_Layer_BackGround(const wstring& strLayerTag)
{
	// 	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Terrain"))))
	// 		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_BOSS2, strLayerTag, TEXT("Prototype_GameObject_Sky"))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_BOSS2, strLayerTag, TEXT("Prototype_GameObject_Map3"))))
		return E_FAIL;

	return S_OK;

}
HRESULT CLevel_BossStage2::Load_Objects_With_Json(string filePath)
{
	json json_in;
	m_pGameInstance->Load_Json(filePath, json_in);

	for (auto& item : json_in.items())
	{
		json object = item.value();

		string tagObject = "Prototype_GameObject_";

		string targetName = object["Name"];
		tagObject += targetName;

		string tagLayer = object["LayerTag"];

		//tagLayer += object["LayerTag"];

		wstring wStringLayerTag;
		wStringLayerTag.assign(tagLayer.begin(), tagLayer.end());

		wstring wStringObjTag;
		wStringObjTag.assign(tagObject.begin(), tagObject.end());


		if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_BOSS2, wStringLayerTag, wStringObjTag)))
			return E_FAIL;

		list<CGameObject*>* pGameObjects = m_pGameInstance->Get_GameObjects(LEVEL_BOSS2, wStringLayerTag);
		if (nullptr == pGameObjects)
			continue;

		CGameObject* pGameObject = pGameObjects->back();
		if (nullptr == pGameObject)
			continue;

		_float4x4 WorldMatrix;
		ZeroMemory(&WorldMatrix, sizeof(_float4x4));
		CJson_Utility::Load_JsonFloat4x4(object["Component"]["Transform"], WorldMatrix);

		pGameObject->Set_WorldMatrix(WorldMatrix);

	}

	return S_OK;
}
CLevel_BossStage2* CLevel_BossStage2::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CLevel_BossStage2* pInstance = new CLevel_BossStage2(pDevice, pContext);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_BossStage2");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_BossStage2::Free()
{
	__super::Free();

}
