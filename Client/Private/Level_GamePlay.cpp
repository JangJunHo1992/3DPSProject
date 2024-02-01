#include "stdafx.h"
#include "Level_GamePlay.h"
#include "GameInstance.h"
#include "Camera_Dynamic.h"
#include "Level_Loading.h"
#include "Monster.h"
#include "Player.h"
#include "Light.h"


CLevel_GamePlay::CLevel_GamePlay(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CLevel(pDevice, pContext)
{
}

HRESULT CLevel_GamePlay::Initialize()
{
	Load_Objects_With_Json("Save_GameObjects1.json");


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
	list<CGameObject*>* playerList = m_pGameInstance->Get_GameObjects(LEVEL_GAMEPLAY, TEXT("Layer_Player"));
	pPlayer = dynamic_cast<CCharacter*>((*playerList).back());
	m_pGameInstance->Set_Player(pPlayer);

	_vector vPos = pPlayer->Get_TransformComp()->Get_State(CTransform::STATE::STATE_POSITION);
	pPlayer->Get_Navigation()->Reset_CurrentIndex(vPos);

	list<CGameObject*>* monsterList = m_pGameInstance->Get_GameObjects(LEVEL_GAMEPLAY, TEXT("Layer_Monster"));

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

	Load_Objects_With_Json("Save_GameObjects.json");

	return S_OK;
}

void CLevel_GamePlay::Tick(_float fTimeDelta)
{
	if (m_pGameInstance->Get_DIKeyState(DIK_F3) & 0x80)
	{
		if (FAILED(m_pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pContext, LEVEL_BOSS1))))
			return;
	}

}

HRESULT CLevel_GamePlay::Render()
{
	SetWindowText(g_hWnd, TEXT("게임플레이레벨입니다."));
	
	return S_OK;
}

HRESULT CLevel_GamePlay::Load_Objects_With_Json(string filePath)
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


		if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, wStringLayerTag, wStringObjTag)))
			return E_FAIL;

		list<CGameObject*>* pGameObjects = m_pGameInstance->Get_GameObjects(LEVEL_GAMEPLAY, wStringLayerTag);
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

HRESULT CLevel_GamePlay::Ready_LightDesc()
{
	LIGHT_DESC			LightDesc{};
	_float darknessFactor = 0.7f;
	LightDesc.eType = LIGHT_DESC::TYPE_DIRECTIONAL;
	LightDesc.vDirection = _float4(0.f, -1.f, 0.f, 0.f);
	LightDesc.vDiffuse = _float4(0.1f, 0.2f, 0.2f, 1.f);
	LightDesc.vAmbient = _float4(0.1f, 0.1f, 0.1f, 1.f);
	//LightDesc.vSpecular = _float4(1.f, 1.f, 1.f, 1.f);
	//_float4(0.4f, 0.5f, 0.6f, 1.f);
	if (FAILED(m_pGameInstance->Add_Light(LightDesc)))
		return E_FAIL;

	/// //////////////////////////////////////////////////

	ZeroMemory(&LightDesc, sizeof LightDesc);

	LightDesc.eType = LIGHT_DESC::TYPE_POINT;
	LightDesc.vPosition = _float4(1.4724184274673462f, 11.77269458770752f, 0.6472334861755371f, 1.f);
	LightDesc.fRange = 20.f;
	LightDesc.vDiffuse = _float4(1.0f, 0.5f, 0.0f, 1.0f) * darknessFactor;
	LightDesc.vAmbient = _float4(0.2f, 0.2f, 0.2f, 1.f);
	
	if (FAILED(m_pGameInstance->Add_Light(LightDesc)))
		return E_FAIL;
	/////////////////////////////////////////////////////////
	ZeroMemory(&LightDesc, sizeof LightDesc);

	LightDesc.eType = LIGHT_DESC::TYPE_POINT;
	LightDesc.vPosition = _float4(1.700891375541687f, 11.783430099487305f, 5.648001194000244f, 1.f);
	LightDesc.fRange = 20.f;
	LightDesc.vDiffuse = _float4(1.0f, 0.5f, 0.0f, 1.0f) * darknessFactor;
	LightDesc.vAmbient = _float4(0.2f, 0.2f, 0.2f, 1.f);

	if (FAILED(m_pGameInstance->Add_Light(LightDesc)))
		return E_FAIL;
	/////////////////////////////////////////////////////////
	ZeroMemory(&LightDesc, sizeof LightDesc);

	LightDesc.eType = LIGHT_DESC::TYPE_POINT;
	LightDesc.vPosition = _float4(112.3560562133789f, 0.5234057903289795f, -10.380002975463867, 1.f);
	LightDesc.fRange = 20.f;
	LightDesc.vDiffuse = _float4(1.0f, 0.5f, 0.0f, 1.0f) * darknessFactor;
	LightDesc.vAmbient = _float4(0.2f, 0.2f, 0.2f, 1.f);

	if (FAILED(m_pGameInstance->Add_Light(LightDesc)))
		return E_FAIL;
	/////////////////////////////////////////////////////////
	ZeroMemory(&LightDesc, sizeof LightDesc);

	LightDesc.eType = LIGHT_DESC::TYPE_POINT;
	LightDesc.vPosition = _float4(99.86543273925781f, 1.063599705696106f, -7.615180969238281f, 1.f);
	LightDesc.fRange = 20.f;
	LightDesc.vDiffuse = _float4(1.0f, 0.5f, 0.0f, 1.0f) * darknessFactor;
	LightDesc.vAmbient = _float4(0.2f, 0.2f, 0.2f, 1.f);

	if (FAILED(m_pGameInstance->Add_Light(LightDesc)))
		return E_FAIL;
	/////////////////////////////////////////////////////////
	ZeroMemory(&LightDesc, sizeof LightDesc);

	LightDesc.eType = LIGHT_DESC::TYPE_POINT;
	LightDesc.vPosition = _float4(82.26553344726563f, 1.5634887218475342f, -3.986800193786621, 1.f);
	LightDesc.fRange = 20.f;
	LightDesc.vDiffuse = _float4(1.0f, 0.5f, 0.0f, 1.0f) * darknessFactor;
	LightDesc.vAmbient = _float4(0.2f, 0.2f, 0.2f, 1.f);

	if (FAILED(m_pGameInstance->Add_Light(LightDesc)))
		return E_FAIL;
	/////////////////////////////////////////////////////////
	ZeroMemory(&LightDesc, sizeof LightDesc);

	LightDesc.eType = LIGHT_DESC::TYPE_POINT;
	LightDesc.vPosition = _float4(85.90026092529297f, 7.649482250213623f, -16.342212677001953, 1.f);
	LightDesc.fRange = 20.f;
	LightDesc.vDiffuse = _float4(1.0f, 0.5f, 0.0f, 1.0f) * darknessFactor;
	LightDesc.vAmbient = _float4(0.2f, 0.2f, 0.2f, 1.f);

	if (FAILED(m_pGameInstance->Add_Light(LightDesc)))
		return E_FAIL;
	/////////////////////////////////////////////////////////
	ZeroMemory(&LightDesc, sizeof LightDesc);

	LightDesc.eType = LIGHT_DESC::TYPE_POINT;
	LightDesc.vPosition = _float4(80.60698699951172f, 7.687834739685059f, -15.370453834533691, 1.f);
	LightDesc.fRange = 20.f;
	LightDesc.vDiffuse = _float4(1.0f, 0.5f, 0.0f, 1.0f) * darknessFactor;
	LightDesc.vAmbient = _float4(0.2f, 0.2f, 0.2f, 1.f);

	if (FAILED(m_pGameInstance->Add_Light(LightDesc)))
		return E_FAIL;
	/////////////////////////////////////////////////////////
	ZeroMemory(&LightDesc, sizeof LightDesc);

	LightDesc.eType = LIGHT_DESC::TYPE_POINT;
	LightDesc.vPosition = _float4(102.6769027709961f, 7.55126428604126f, -32.740867614746094, 1.f);
	LightDesc.fRange = 20.f;
	LightDesc.vDiffuse = _float4(1.0f, 0.5f, 0.0f, 1.0f) * darknessFactor;
	LightDesc.vAmbient = _float4(0.2f, 0.2f, 0.2f, 1.f);

	if (FAILED(m_pGameInstance->Add_Light(LightDesc)))
		return E_FAIL;
	/////////////////////////////////////////////////////////

	ZeroMemory(&LightDesc, sizeof LightDesc);

	LightDesc.eType = LIGHT_DESC::TYPE_POINT;
	LightDesc.vPosition = _float4(124.58329010009766f, 7.928438186645508f, -24.89158058166504, 1.f);
	LightDesc.fRange = 20.f;
	LightDesc.vDiffuse = _float4(1.0f, 0.5f, 0.0f, 1.0f) * darknessFactor;
	LightDesc.vAmbient = _float4(0.2f, 0.2f, 0.2f, 1.f);

	if (FAILED(m_pGameInstance->Add_Light(LightDesc)))
		return E_FAIL;
	/////////////////////////////////////////////////////////
	ZeroMemory(&LightDesc, sizeof LightDesc);

	LightDesc.eType = LIGHT_DESC::TYPE_POINT;
	LightDesc.vPosition = _float4(115.4299087524414f, 7.551743984222412f, 8.650155067443848f, 1.f);
	LightDesc.fRange = 20.f;
	LightDesc.vDiffuse = _float4(1.0f, 0.5f, 0.0f, 1.0f) * darknessFactor;
	LightDesc.vAmbient = _float4(0.2f, 0.2f, 0.2f, 1.f);

	if (FAILED(m_pGameInstance->Add_Light(LightDesc)))
		return E_FAIL;
	/////////////////////////////////////////////////////////


	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Camera(const wstring& strLayerTag)
{
	CCamera_Dynamic::DYNAMIC_CAMERA_DESC		Desc = {};

	Desc.fMouseSensor = 0.05f;
	Desc.vEye = _float4(0.f, 20.f,-15.f, 1.f);
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
	//if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Player"))))
	//	return E_FAIL;

	
	//if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Covus"))))
	//	return E_FAIL;

	list<CGameObject*> m_pPlayerLayer = *m_pGameInstance->Get_GameObjects(LEVEL_GAMEPLAY, strLayerTag);

	CGameObject* pPlayer = m_pPlayerLayer.back();

	m_pGameInstance->Set_Player(pPlayer);

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Monster(const wstring& strLayerTag)
{
	
// 	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Monster"))))
// 		return E_FAIL;
// 	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Magician"))))
// 		return E_FAIL;
// 	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Varg"))))
// 		return E_FAIL;
	//if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_JobMob1"))))
	//	return E_FAIL;
	//if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_JobMob2"))))
	//	return E_FAIL;

	return S_OK;
}
HRESULT CLevel_GamePlay::Ready_Layer_Effect(const wstring& strLayerTag)
{
// 	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Particle_Blue"))))
// 		return E_FAIL;

// 	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Particle_Red"))))
// 		return E_FAIL;

	return S_OK;
}
HRESULT CLevel_GamePlay::Ready_Layer_BackGround(const wstring& strLayerTag)
{
// 	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Terrain"))))
// 		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Sky"))))
		return E_FAIL;

// 	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_GAMEPLAY, strLayerTag, TEXT("Prototype_GameObject_Map"))))
// 		return E_FAIL;

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
