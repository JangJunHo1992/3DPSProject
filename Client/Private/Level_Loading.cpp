#include "stdafx.h"
#include "Level_Loading.h"
#include "Loader.h"

#include "GameInstance.h"
#include "GameObject.h"

#include "Level_Logo.h"
#include "Level_GamePlay.h"
#include "Level_MapTool.h"

#include "Level_Stage1.h"
#include "Level_BossStage1.h"
#include "Level_BossStage2.h"
#include "Level_EffectTool.h"

#include "Loading1.h"
#include "Loading2.h"
#include "Loading3.h"
#include "TexUI_Loading_ICON.h"
#include "TexUI_Loading_Complete.h"
#include "TexUI_Stage1Loading_pont.h"
#include "TexUI_Stage2Loading_pont.h"
#include "TexUI_Stage3Loading_pont.h"
#include "TexUI_Stage1Loading_Name.h"
#include "TexUI_Stage2Loading_Name.h"
#include "TexUI_Stage3Loading_Name.h"

#include "Imgui_Manager.h"
CLevel_Loading::CLevel_Loading(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CLevel(pDevice, pContext)
{

}

HRESULT CLevel_Loading::Initialize(LEVEL eNextLevelID)
{
	/* ���� �ε� ������ ������ ���� �������� �״� ������ �Ѿ�����ؼ�. */
	m_eNextLevelID = eNextLevelID;
	m_iNextLevel = m_eNextLevelID;
	/* ���ν������ ���� �ε��Ѵ�. */

	/* �ε��� �ڿ��� �ε��Ѵ�. */
	/* For.Prototype_Component_Texture_Loading1 */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_LOADING, TEXT("Prototype_Component_Texture_Loading1"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/LoadingScreen/TexUI_LoadingScreen_Lobby_01.dds"), 1))))
		return E_FAIL;
	/* For.Prototype_Component_Texture_Loading2 */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_LOADING, TEXT("Prototype_Component_Texture_Loading2"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/LoadingScreen/TexUI_LoadingScreen_Fortress_01.dds"), 1))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_Loading3 */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_LOADING, TEXT("Prototype_Component_Texture_Loading3"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/LoadingScreen/TexUI_LoadingScreen_Circus_01.dds"), 1))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_TexUI_Loading_ICON */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_LOADING, TEXT("Prototype_Component_Texture_TexUI_Loading_ICON"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/LoadingScreen/TexUI_LoadingIcon.png"), 1))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_TexUI_Loading_Complete */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_LOADING, TEXT("Prototype_Component_Texture_TexUI_Loading_Complete"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/LoadingScreen/Loading_Complete.png"), 1))))
		return E_FAIL;
	//=============================Font============================================
	/* For.Prototype_Component_Texture_TexUI_Stage1Loading_pont */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_LOADING, TEXT("Prototype_Component_Texture_TexUI_Stage1Loading_pont"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/LoadingScreen/LoadingFont/Fortress_Desc.png"), 1))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_TexUI_Stage2Loading_pont */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_LOADING, TEXT("Prototype_Component_Texture_TexUI_Stage2Loading_pont"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/LoadingScreen/LoadingFont/SafeHouse_Desc.png"), 1))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_TexUI_Stage3Loading_pont */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_LOADING, TEXT("Prototype_Component_Texture_TexUI_Stage3Loading_pont"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/LoadingScreen/LoadingFont/SeaOfTrees_Desc.png"), 1))))
		return E_FAIL;
	//=============================FontName============================================
/* For.Prototype_Component_Texture_TexUI_Stage1Loading_Name */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_LOADING, TEXT("Prototype_Component_Texture_TexUI_Stage1Loading_Name"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/LoadingScreen/LoadingFont/Fortress_Name.png"), 1))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_TexUI_Stage2Loading_Name */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_LOADING, TEXT("Prototype_Component_Texture_TexUI_Stage2Loading_Name"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/LoadingScreen/LoadingFont/SafeHouse_Name.png"), 1))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_TexUI_Stage3Loading_Name */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_LOADING, TEXT("Prototype_Component_Texture_TexUI_Stage3Loading_Name"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/LoadingScreen/LoadingFont/SeaOfTrees_Name.png"), 1))))
		return E_FAIL;
	
	/* �ε��������� ��������� ��ü���� �����Ѵ�.(���, �Ϸ���Ʈ, �ε���) */
	if (m_eNextLevelID == LEVEL_GAMEPLAY)
	{
		if (FAILED(Ready_Layer_BackGround1(TEXT("Layer_BackGround"))))
			return E_FAIL;
		//CGameObject::m_bLoadingComplete = false;
	}
	else if (m_eNextLevelID == LEVEL_BOSS1)
	{
		if (FAILED(Ready_Layer_BackGround2(TEXT("Layer_BackGround"))))
			return E_FAIL;
		//CGameObject::m_bLoadingComplete = false;
	}
	else if (m_eNextLevelID == LEVEL_BOSS2)
	{
		if (FAILED(Ready_Layer_BackGround3(TEXT("Layer_BackGround"))))
			return E_FAIL;
		//CGameObject::m_bLoadingComplete = false;
	}
	/* �߰����� �����带 �����Ͽ� eNextLevelID�� �ʿ��� �ڿ����� �ε��Ѵ�. */
	m_pLoader = CLoader::Create(m_pDevice, m_pContext, eNextLevelID);
	if (nullptr == m_pLoader)
		return E_FAIL;

	m_pGameInstance->Play_BGM(L"BGM", L"MainLoading.ogg", 1.f);

	return S_OK;
}

void CLevel_Loading::Tick(_float fTimeDelta)
{
	if (nullptr == m_pGameInstance)
		return;

	if (true == m_pLoader->isFinished())
	{
 		if (GetKeyState(VK_RETURN) & 0x8000)
 		{
			CLevel*		pNewLevel = { nullptr };

			

			switch (m_eNextLevelID)
			{
			case LEVEL_LOGO:
				pNewLevel = CLevel_Logo::Create(m_pDevice, m_pContext);
				break;
			case LEVEL_GAMEPLAY:
				pNewLevel = CLevel_GamePlay::Create(m_pDevice, m_pContext);
				break;
			case LEVEL_STAGE1:
				pNewLevel = CLevel_Stage1::Create(m_pDevice, m_pContext);
				break;
			case LEVEL_BOSS1:
				pNewLevel = CLevel_BossStage1::Create(m_pDevice, m_pContext);
				break;
			case LEVEL_BOSS2:
				pNewLevel = CLevel_BossStage2::Create(m_pDevice, m_pContext);
				break;
			case LEVEL_TOOL:
				pNewLevel = CLevel_MapTool::Create(m_pDevice, m_pContext);
				break;
			case LEVEL_EFFECT_TOOL:
				pNewLevel = CLevel_EffectTool::Create(m_pDevice, m_pContext);
				break;
			}
			CGameObject::m_bLoadingComplete = false;
			//! �¿� �ּ�if (nullptr == pNewLevel)
			//! �¿� �ּ�	return;
			if (FAILED(m_pGameInstance->Open_Level(m_eNextLevelID, pNewLevel)))
				return;
		}
	}
}

HRESULT CLevel_Loading::Render()
{
	m_pLoader->Print_LoadingText();

	return S_OK;
}

HRESULT CLevel_Loading::Ready_Layer_BackGround1(const wstring& strLayerTag)
{
	{
	CLoading1::Loading1_DESC		BackGroundDesc = {};

	BackGroundDesc.fX = g_iWinSizeX >> 1;
	BackGroundDesc.fY = g_iWinSizeY >> 1;
	BackGroundDesc.fSizeX = g_iWinSizeX;
	BackGroundDesc.fSizeY = g_iWinSizeY;
	BackGroundDesc.fRotationPerSec = XMConvertToRadians(90.f);
	BackGroundDesc.fSpeedPerSec = 10.f;
	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_LOADING, strLayerTag, TEXT("Prototype_GameObject_Loading1"), &BackGroundDesc)))
		return E_FAIL;
	}

	{
		CTexUI_Loading_ICON::TexUI_Loading_ICON_DESC		BackGroundDesc = {};

		BackGroundDesc.fX = 1180 ;
		BackGroundDesc.fY = 610 ;
		BackGroundDesc.fSizeX = g_iWinSizeX * 0.06f;
		BackGroundDesc.fSizeY = g_iWinSizeY * 0.25f;
		BackGroundDesc.fRotationPerSec = XMConvertToRadians(90.f);
		BackGroundDesc.fSpeedPerSec = 10.f;

		if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_LOADING, strLayerTag, TEXT("Prototype_GameObject_TexUI_Loading_ICON"), &BackGroundDesc)))
			return E_FAIL;
	}


	{
		CTexUI_Loading_Complete::TexUI_Loading_Complete_DESC		BackGroundDesc = {};

		BackGroundDesc.fX = 1130;
		BackGroundDesc.fY = 650;
		BackGroundDesc.fSizeX = g_iWinSizeX * 0.4f;
		BackGroundDesc.fSizeY = g_iWinSizeY * 0.1f;
		BackGroundDesc.fRotationPerSec = XMConvertToRadians(90.f);
		BackGroundDesc.fSpeedPerSec = 10.f;

		if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_LOADING, strLayerTag, TEXT("Prototype_GameObject_TexUI_Loading_Complete"), &BackGroundDesc)))
			return E_FAIL;
	}

	{
		CTexUI_Stage1Loading_pont::TexUI_Stage1Loading_pont_DESC		BackGroundDesc = {};

		BackGroundDesc.fX = 480;
		BackGroundDesc.fY = 670;
		BackGroundDesc.fSizeX = g_iWinSizeX * 0.7f;
		BackGroundDesc.fSizeY = g_iWinSizeY * 0.06f;
		BackGroundDesc.fRotationPerSec = XMConvertToRadians(90.f);
		BackGroundDesc.fSpeedPerSec = 10.f;

		if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_LOADING, strLayerTag, TEXT("Prototype_GameObject_TexUI_Stage1Loading_pont"), &BackGroundDesc)))
			return E_FAIL;
	}

	{
		CTexUI_Stage1Loading_Name::TexUI_Stage1Loading_Name_DESC		BackGroundDesc = {};

		BackGroundDesc.fX = 90;
		BackGroundDesc.fY = 620;
		BackGroundDesc.fSizeX = g_iWinSizeX * 0.1f;
		BackGroundDesc.fSizeY = g_iWinSizeY * 0.03f;
		BackGroundDesc.fRotationPerSec = XMConvertToRadians(90.f);
		BackGroundDesc.fSpeedPerSec = 10.f;

		if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_LOADING, strLayerTag, TEXT("Prototype_GameObject_TexUI_Stage1Loading_Name"), &BackGroundDesc)))
			return E_FAIL;
	}
	
	
	return S_OK;
}

HRESULT CLevel_Loading::Ready_Layer_BackGround2(const wstring& strLayerTag)
{
	{
	CLoading2::Loading2_DESC		BackGroundDesc = {};

	BackGroundDesc.fX = g_iWinSizeX >> 1;
	BackGroundDesc.fY = g_iWinSizeY >> 1;
	BackGroundDesc.fSizeX = g_iWinSizeX;
	BackGroundDesc.fSizeY = g_iWinSizeY;
	BackGroundDesc.fRotationPerSec = XMConvertToRadians(90.f);
	BackGroundDesc.fSpeedPerSec = 10.f;

	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_LOADING, strLayerTag, TEXT("Prototype_GameObject_Loading2"), &BackGroundDesc)))
		return E_FAIL;
	}

	{
		CTexUI_Loading_ICON::TexUI_Loading_ICON_DESC		BackGroundDesc = {};

		BackGroundDesc.fX = 1180;
		BackGroundDesc.fY = 610;
		BackGroundDesc.fSizeX = g_iWinSizeX * 0.06f;
		BackGroundDesc.fSizeY = g_iWinSizeY * 0.25f;
		BackGroundDesc.fRotationPerSec = XMConvertToRadians(90.f);
		BackGroundDesc.fSpeedPerSec = 10.f;

		if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_LOADING, strLayerTag, TEXT("Prototype_GameObject_TexUI_Loading_ICON"), &BackGroundDesc)))
			return E_FAIL;
	}

	{
		CTexUI_Loading_Complete::TexUI_Loading_Complete_DESC		BackGroundDesc = {};

		BackGroundDesc.fX = 1130;
		BackGroundDesc.fY = 650;
		BackGroundDesc.fSizeX = g_iWinSizeX * 0.4f;
		BackGroundDesc.fSizeY = g_iWinSizeY * 0.1f;
		BackGroundDesc.fRotationPerSec = XMConvertToRadians(90.f);
		BackGroundDesc.fSpeedPerSec = 10.f;

		if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_LOADING, strLayerTag, TEXT("Prototype_GameObject_TexUI_Loading_Complete"), &BackGroundDesc)))
			return E_FAIL;
	}

	{
		CTexUI_Stage2Loading_pont::TexUI_Stage2Loading_pont_DESC		BackGroundDesc = {};

		BackGroundDesc.fX = 480;
		BackGroundDesc.fY = 670;
		BackGroundDesc.fSizeX = g_iWinSizeX * 0.7f;
		BackGroundDesc.fSizeY = g_iWinSizeY * 0.06f;
		BackGroundDesc.fRotationPerSec = XMConvertToRadians(90.f);
		BackGroundDesc.fSpeedPerSec = 10.f;

		if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_LOADING, strLayerTag, TEXT("Prototype_GameObject_TexUI_Stage2Loading_pont"), &BackGroundDesc)))
			return E_FAIL;
	}

	{
		CTexUI_Stage2Loading_Name::TexUI_Stage2Loading_Name_DESC		BackGroundDesc = {};

		BackGroundDesc.fX = 90;
		BackGroundDesc.fY = 620;
		BackGroundDesc.fSizeX = g_iWinSizeX * 0.1f;
		BackGroundDesc.fSizeY = g_iWinSizeY * 0.03f;
		BackGroundDesc.fRotationPerSec = XMConvertToRadians(90.f);
		BackGroundDesc.fSpeedPerSec = 10.f;

		if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_LOADING, strLayerTag, TEXT("Prototype_GameObject_TexUI_Stage2Loading_Name"), &BackGroundDesc)))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CLevel_Loading::Ready_Layer_BackGround3(const wstring& strLayerTag)
{
	{
	CLoading3::Loading3_DESC		BackGroundDesc = {};

	BackGroundDesc.fX = g_iWinSizeX >> 1;
	BackGroundDesc.fY = g_iWinSizeY >> 1;
	BackGroundDesc.fSizeX = g_iWinSizeX;
	BackGroundDesc.fSizeY = g_iWinSizeY;
	BackGroundDesc.fRotationPerSec = XMConvertToRadians(90.f);
	BackGroundDesc.fSpeedPerSec = 10.f;

	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_LOADING, strLayerTag, TEXT("Prototype_GameObject_Loading3"), &BackGroundDesc)))
		return E_FAIL;
	}

	{
		CTexUI_Loading_ICON::TexUI_Loading_ICON_DESC		BackGroundDesc = {};

		BackGroundDesc.fX = 1180;
		BackGroundDesc.fY = 610;
		BackGroundDesc.fSizeX = g_iWinSizeX * 0.06f;
		BackGroundDesc.fSizeY = g_iWinSizeY * 0.25f;
		BackGroundDesc.fRotationPerSec = XMConvertToRadians(90.f);
		BackGroundDesc.fSpeedPerSec = 10.f;

		if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_LOADING, strLayerTag, TEXT("Prototype_GameObject_TexUI_Loading_ICON"), &BackGroundDesc)))
			return E_FAIL;
	}

	{
		CTexUI_Loading_Complete::TexUI_Loading_Complete_DESC		BackGroundDesc = {};

		BackGroundDesc.fX = 1130;
		BackGroundDesc.fY = 650;
		BackGroundDesc.fSizeX = g_iWinSizeX * 0.4f;
		BackGroundDesc.fSizeY = g_iWinSizeY * 0.1f;
		BackGroundDesc.fRotationPerSec = XMConvertToRadians(90.f);
		BackGroundDesc.fSpeedPerSec = 10.f;

		if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_LOADING, strLayerTag, TEXT("Prototype_GameObject_TexUI_Loading_Complete"), &BackGroundDesc)))
			return E_FAIL;
	}

	{
		CTexUI_Stage3Loading_pont::TexUI_Stage3Loading_pont_DESC		BackGroundDesc = {};

		BackGroundDesc.fX = 480;
		BackGroundDesc.fY = 670;
		BackGroundDesc.fSizeX = g_iWinSizeX * 0.7f;
		BackGroundDesc.fSizeY = g_iWinSizeY * 0.06f;
		BackGroundDesc.fRotationPerSec = XMConvertToRadians(90.f);
		BackGroundDesc.fSpeedPerSec = 10.f;

		if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_LOADING, strLayerTag, TEXT("Prototype_GameObject_TexUI_Stage3Loading_pont"), &BackGroundDesc)))
			return E_FAIL;
	}

	{
		CTexUI_Stage3Loading_Name::TexUI_Stage3Loading_Name_DESC		BackGroundDesc = {};

		BackGroundDesc.fX = 90;
		BackGroundDesc.fY = 620;
		BackGroundDesc.fSizeX = g_iWinSizeX * 0.1f;
		BackGroundDesc.fSizeY = g_iWinSizeY * 0.03f;
		BackGroundDesc.fRotationPerSec = XMConvertToRadians(90.f);
		BackGroundDesc.fSpeedPerSec = 10.f;

		if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_LOADING, strLayerTag, TEXT("Prototype_GameObject_TexUI_Stage3Loading_Name"), &BackGroundDesc)))
			return E_FAIL;
	}

	return S_OK;
}

CLevel_Loading * CLevel_Loading::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, LEVEL eNextLevelID)
{
	CLevel_Loading*		pInstance = new CLevel_Loading(pDevice, pContext);

	if (FAILED(pInstance->Initialize(eNextLevelID)))
	{
		MSG_BOX("Failed to Created : CLevel_Loading");
		Safe_Release(pInstance);
	}
	return pInstance; 
}

void CLevel_Loading::Free()
{
	__super::Free();

	Safe_Release(m_pLoader);

}
