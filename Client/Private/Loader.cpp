#include "stdafx.h"
#include "Loader.h"
#include "GameInstance.h"
#include "BackGround.h"
#include "Navigation.h"
//#include "VIBuffer_Dynamic_Terrain.h"
#include "VIBuffer_Static_Terrain.h"
#include "VIBuffer_Dynamic_Plane.h"

#include "Terrain_Tool.h"
#include "Terrain_GamePlay.h"

#include "ForkLift_Tool.h"
#include "ForkLift_GamePlay.h"

#include "Monster_Tool.h"
#include "Monster_GamePlay.h"

#include "Raider_Tool.h"
#include "Raider_GamePlay.h"

#include "Model_Tool.h"
#include "Model_GamePlay.h"

#include "Player.h"

#include "Camera_Dynamic.h"
#include "Camera_Dynamic_Tool.h"
#include <process.h>



CLoader::CLoader(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: m_pDevice(pDevice)
	, m_pContext(pContext)
	, m_pGameInstance(CGameInstance::GetInstance())
{
	Safe_AddRef(m_pGameInstance);
	Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pContext);
}

// typedef unsigned(__stdcall* _beginthreadex_proc_type)(void*);

_uint APIENTRY LoadingThread(void* pArg)
{
	CoInitializeEx(nullptr, 0);

	CLoader*		pLoader = (CLoader*)pArg;

	pLoader->Loading();
	
	return 0;
}


HRESULT CLoader::Initialize(LEVEL eNextLevelID)
{
	/* 어떤 레벨의 자원을 로드해야하는지? */
	m_eNextLevelID = eNextLevelID;

	InitializeCriticalSection(&m_CriticalSection);

	/* 스레드를 생성한다. */
	/* LoadingThread : 생성한 스레드가 가장 먼저 호출해야할 함수 */
	/* this : 위 함수를 호출하면서 인자로 전달할 데이터. */
	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, LoadingThread, this, 0, nullptr);
	if (0 == m_hThread)
		return E_FAIL;

	return S_OK;
}

void CLoader::Print_LoadingText()
{
	SetWindowText(g_hWnd, m_szLoadingText);
}

HRESULT CLoader::Loading()
{
	EnterCriticalSection(&m_CriticalSection);

	HRESULT hr = 0;

	switch (m_eNextLevelID)
	{
	case LEVEL_LOGO:
		hr = Loading_For_Logo_Level();
		break;

	case LEVEL_GAMEPLAY:		
		hr = Loading_For_GamePlay_Level();
		break;
	case LEVEL_TOOL:
		hr = Loading_For_Tool_Level();
	}

	if (FAILED(hr))
		return E_FAIL;

	LeaveCriticalSection(&m_CriticalSection);

	return S_OK;
}

HRESULT CLoader::Loading_For_Logo_Level()
{
	/* 로고 레벨에 필요한 자원을 로드하자. */
	lstrcpy(m_szLoadingText, TEXT("텍스쳐를 로드하는 중입니다."));

	/* For.Prototype_Component_Texture_Logo */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_LOGO, TEXT("Prototype_Component_Texture_Logo"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Default%d.jpg"), 2))))
		return E_FAIL;


	lstrcpy(m_szLoadingText, TEXT("모델를(을) 로드하는 중입니다."));
	

	lstrcpy(m_szLoadingText, TEXT("셰이더를(을) 로드하는 중입니다."));
	

	lstrcpy(m_szLoadingText, TEXT("원형객체를(을) 로드하는 중입니다."));

	/* For.Prototype_GameObject_BackGround */
	if (FAILED(m_pGameInstance->Add_Prototype_Object(TEXT("Prototype_GameObject_BackGround"),
		CBackGround::Create(m_pDevice, m_pContext))))
		return E_FAIL;	

	lstrcpy(m_szLoadingText, TEXT("로딩이 완료되었습니다."));

	m_isFinished = true;

	return S_OK;
}

HRESULT CLoader::Loading_For_Level(LEVEL eLEVEL)
{
	/* 게임플레이 레벨에 필요한 자원을 로드하자. */
	lstrcpy(m_szLoadingText, TEXT("텍스쳐를 로드하는 중입니다."));

	/* For.Prototype_Component_Texture_Terrain */
	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Texture_Terrain"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Terrain/Tile%d.dds"), 2))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_Terrain_Mask */
	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Texture_Terrain_Mask"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Terrain/MyMask.dds"), 1))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_Terrain_Brush */
	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Texture_Terrain_Brush"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Terrain/Brush.png"), 1))))
		return E_FAIL;

	lstrcpy(m_szLoadingText, TEXT("모델를(을) 로드하는 중입니다."));


	_matrix		PivotMatrix;

	if (LEVEL_TOOL == eLEVEL)
	{

	}
	else 
	{
		/* For.Prototype_Component_Model_Fiona */
		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		if (FAILED(m_pGameInstance->Add_Prototype(LEVEL::LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Fiona_GamePlay"),
			CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_ANIM, "../Bin/Resources/Models/DesmondDemon/S_Desmond_Demon_Form.fbx", PivotMatrix))))
			return E_FAIL;
	}

	if (LEVEL_TOOL == eLEVEL)
	{
		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		if (FAILED(m_pGameInstance->Add_Prototype(LEVEL::LEVEL_TOOL, TEXT("Prototype_Component_Model_Raider_Tool"),
			CModel_Tool::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, "../Bin/Resources/Models/King/King.fbx", PivotMatrix))))
			return E_FAIL;
	}
	else
	{
		/* For.Prototype_Component_Model_ForkLift */
		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		if (FAILED(m_pGameInstance->Add_Prototype(LEVEL::LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_ForkLift_GamePlay"),
			CModel_GamePlay::Create(m_pDevice, m_pContext, CModel::TYPE_NONANIM, "../Bin/Resources/Models/ForkLift/ForkLift.fbx", PivotMatrix))))
			return E_FAIL;
	}

	if (LEVEL_TOOL == eLEVEL) 
	{
		/* For.Prototype_Component_VIBuffer_Terrain */
		if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_VIBuffer_Terrain_Tool"),
			CVIBuffer_Dynamic_Terrain::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Terrain/Height2.bmp")))))
			return E_FAIL;

		/* For.Prototype_Component_VIBuffer_Plane */
		if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_VIBuffer_Plane_Tool"),
			CVIBuffer_Dynamic_Plane::Create(m_pDevice, m_pContext, 50, 50))))
			return E_FAIL;
	}
	else 
	{
		/* For.Prototype_Component_VIBuffer_Terrain */
		if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_VIBuffer_Terrain_GamePlay"),
			CVIBuffer_Static_Terrain::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Terrain/Height2.bmp")))))
			return E_FAIL;
	}


	
	lstrcpy(m_szLoadingText, TEXT("셰이더를(을) 로드하는 중입니다."));
	/* For.Prototype_Component_Shader_VtxNorTex */
	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Shader_VtxNorTex"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxNorTex.hlsl"), VTXNORTEX::Elements, VTXNORTEX::iNumElements))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_Model */
	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Shader_Model"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_Model.hlsl"), VTXMESH::Elements, VTXMESH::iNumElements))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_AnimModel */
	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Shader_AnimModel"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_AnimModel.hlsl"), VTXANIMMESH::Elements, VTXANIMMESH::iNumElements))))
		return E_FAIL;

	lstrcpy(m_szLoadingText, TEXT("네비게이션를(을) 로드하는 중입니다."));
	/* For.Prototype_Component_Navigation */
	if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_Navigation"),
		CNavigation::Create(m_pDevice, m_pContext, TEXT("../Bin/DataFiles/Navigation.dat")))))
		return E_FAIL;

	lstrcpy(m_szLoadingText, TEXT("원형객체를(을) 로드하는 중입니다."));

	if (LEVEL_TOOL == eLEVEL)
	{
	}
	else
	{
		/* For.Prototype_GameObject_Player */
		if (FAILED(m_pGameInstance->Add_Prototype_Object(TEXT("Prototype_GameObject_Player_GamePlay"),
			CPlayer::Create(m_pDevice, m_pContext))))
			return E_FAIL;
	}

	if (LEVEL_TOOL == eLEVEL)
	{
		/* For.Prototype_GameObject_Terrain */
		if (FAILED(m_pGameInstance->Add_Prototype_Object(TEXT("Prototype_GameObject_Terrain_Tool"),
			CTerrain_Tool::Create(m_pDevice, m_pContext))))
			return E_FAIL;

		/* For.Prototype_GameObject_Terrain */
		if (FAILED(m_pGameInstance->Add_Prototype_Object(TEXT("Prototype_GameObject_Plane_Tool"),
			CTerrain_Tool::Create(m_pDevice, m_pContext, true))))
			return E_FAIL;
	}
	else 
	{
		/* For.Prototype_GameObject_Terrain */
		if (FAILED(m_pGameInstance->Add_Prototype_Object(TEXT("Prototype_GameObject_Terrain_GamePlay"),
			CTerrain_GamePlay::Create(m_pDevice, m_pContext))))
			return E_FAIL;
	}

	if (LEVEL_TOOL == eLEVEL)
	{
		/* For.Prototype_GameObject_Raider */
		if (FAILED(m_pGameInstance->Add_Prototype_Object(TEXT("Prototype_GameObject_Raider_Tool"),
			CRaider_Tool::Create(m_pDevice, m_pContext))))
			return E_FAIL;
	}
	else 
	{
		/* For.Prototype_GameObject_Monster */
		if (FAILED(m_pGameInstance->Add_Prototype_Object(TEXT("Prototype_GameObject_Monster_GamePlay"),
			CMonster_GamePlay::Create(m_pDevice, m_pContext))))
			return E_FAIL;
	}

	if (LEVEL_TOOL == eLEVEL)
	{

	}
	else
	{
		/* For.Prototype_GameObject_ForkLift */
		if (FAILED(m_pGameInstance->Add_Prototype_Object(TEXT("Prototype_GameObject_ForkLift_GamePlay"),
			CForkLift_GamePlay::Create(m_pDevice, m_pContext))))
			return E_FAIL;
	}
	if (LEVEL_TOOL == eLEVEL)
	{
		/* For.Prototype_GameObject_Camera_Dynamic */
		if (FAILED(m_pGameInstance->Add_Prototype_Object(TEXT("Prototype_GameObject_Camera_Dynamic_Tool"),
			CCamera_Dynamic_Tool::Create(m_pDevice, m_pContext))))
			return E_FAIL;
	}
	else
	{
		/* For.Prototype_GameObject_Camera_Dynamic */
		if (FAILED(m_pGameInstance->Add_Prototype_Object(TEXT("Prototype_GameObject_Camera_Dynamic"),
			CCamera_Dynamic::Create(m_pDevice, m_pContext))))
			return E_FAIL;
	}

	

	lstrcpy(m_szLoadingText, TEXT("로딩이 완료되었습니다."));

	m_isFinished = true;
	
	return S_OK;
}

HRESULT CLoader::Loading_For_GamePlay_Level()
{
	return Loading_For_Level(LEVEL_GAMEPLAY);
}

HRESULT CLoader::Loading_For_Tool_Level()
{
	return Loading_For_Level(LEVEL_TOOL);
}

CLoader * CLoader::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, LEVEL eNextLevelID)
{
	CLoader*		pInstance = new CLoader(pDevice, pContext);

	if (FAILED(pInstance->Initialize(eNextLevelID)))
	{
		MSG_BOX("Failed to Created : CLoader");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLoader::Free()
{
	WaitForSingleObject(m_hThread, INFINITE);

	DeleteCriticalSection(&m_CriticalSection);

	DeleteObject(m_hThread);

	CloseHandle(m_hThread);

	Safe_Release(m_pGameInstance);
	Safe_Release(m_pDevice);
	Safe_Release(m_pContext);
}
