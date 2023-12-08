#include "stdafx.h"
#include "Loader.h"
#include "GameInstance.h"
#include "BackGround.h"
#include "ForkLift.h"
#include "Terrain_MapTool.h"
#include "Terrain_GamePlay.h"
#include "Monster.h"
#include "Camera_Dynamic.h"
#include <process.h>

#include "Raider.h"

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
	/* � ������ �ڿ��� �ε��ؾ��ϴ���? */
	m_eNextLevelID = eNextLevelID;

	InitializeCriticalSection(&m_CriticalSection);

	/* �����带 �����Ѵ�. */
	/* LoadingThread : ������ �����尡 ���� ���� ȣ���ؾ��� �Լ� */
	/* this : �� �Լ��� ȣ���ϸ鼭 ���ڷ� ������ ������. */
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
	/* �ΰ� ������ �ʿ��� �ڿ��� �ε�����. */
	lstrcpy(m_szLoadingText, TEXT("�ؽ��ĸ� �ε��ϴ� ���Դϴ�."));

	/* For.Prototype_Component_Texture_Logo */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_LOGO, TEXT("Prototype_Component_Texture_Logo"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Default%d.jpg"), 2))))
		return E_FAIL;


	lstrcpy(m_szLoadingText, TEXT("�𵨸�(��) �ε��ϴ� ���Դϴ�."));
	

	lstrcpy(m_szLoadingText, TEXT("���̴���(��) �ε��ϴ� ���Դϴ�."));
	

	lstrcpy(m_szLoadingText, TEXT("������ü��(��) �ε��ϴ� ���Դϴ�."));

	/* For.Prototype_GameObject_BackGround */
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_BackGround"),
		CBackGround::Create(m_pDevice, m_pContext))))
		return E_FAIL;	

	lstrcpy(m_szLoadingText, TEXT("�ε��� �Ϸ�Ǿ����ϴ�."));

	m_isFinished = true;

	return S_OK;
}

template<class T, class T2>
HRESULT CLoader::Loading_For_Level(LEVEL eLEVEL)
{
	
	/* �����÷��� ������ �ʿ��� �ڿ��� �ε�����. */
	lstrcpy(m_szLoadingText, TEXT("�ؽ��ĸ� �ε��ϴ� ���Դϴ�."));
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

	lstrcpy(m_szLoadingText, TEXT("�𵨸�(��) �ε��ϴ� ���Դϴ�."));


	_matrix		PivotMatrix;
	if (eLEVEL == LEVEL_GAMEPLAY)
	{
		/* For.Prototype_Component_VIBuffer_Terrain */
		if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_VIBuffer_Terrain"),
			CVIBuffer_Terrain::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Terrain/Height1.bmp")))))
			return E_FAIL;
	}
	else if (eLEVEL == LEVEL_TOOL)
	{
		/* For.Prototype_Component_VIBuffer_Terrain */
		if (FAILED(m_pGameInstance->Add_Prototype(eLEVEL, TEXT("Prototype_Component_VIBuffer_Terrain"),
			CVIBuffer_Dynamic_Terrain::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/Textures/Terrain/Height1.bmp")))))
			return E_FAIL;
	}
	
	
	lstrcpy(m_szLoadingText, TEXT("���̴���(��) �ε��ϴ� ���Դϴ�."));
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

	lstrcpy(m_szLoadingText, TEXT("������ü��(��) �ε��ϴ� ���Դϴ�."));
	/* For.Prototype_GameObject_Terrain */
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Terrain"),
		T::Create(m_pDevice, m_pContext))))
		return E_FAIL;


	/* For.Prototype_GameObject_Camera_Dynamic */
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Camera_Dynamic"),
		CCamera_Dynamic::Create(m_pDevice, m_pContext))))
		return E_FAIL;

	lstrcpy(m_szLoadingText, TEXT("�ε��� �Ϸ�Ǿ����ϴ�."));

	m_isFinished = true;
	
	return S_OK;
}

HRESULT CLoader::Loading_For_GamePlay_Level()
{
	_matrix		PivotMatrix;

	/* For.Prototype_Component_Model_Fiona */
	PivotMatrix = XMMatrixRotationY(XMConvertToRadians(180.0f));
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL::LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Fiona"),
		CModel::Create(m_pDevice, m_pContext, CModel::TYPE::TYPE_ANIM, "../Bin/Resources/Models/Fiona/Fiona.fbx", PivotMatrix))))
		return E_FAIL;

	/* For.Prototype_Component_Model_ForkLift */
	PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL::LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_ForkLift"),
		CModel::Create(m_pDevice, m_pContext, CModel::TYPE::TYPE_NONANIM, "../Bin/Resources/Models/ForkLift/ForkLift.fbx", PivotMatrix))))
		return E_FAIL;



	if (E_FAIL == Loading_For_Level<CTerrain_GamePlay, CVIBuffer_Terrain>(LEVEL::LEVEL_GAMEPLAY))
		return E_FAIL;



	/* For.Prototype_GameObject_Monster */
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Monster"),
		CMonster::Create(m_pDevice, m_pContext))))
		return E_FAIL;

	/* For.Prototype_GameObject_ForkLift */
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_ForkLift"),
		CForkLift::Create(m_pDevice, m_pContext))))
		return E_FAIL;


	return S_OK;

}

HRESULT CLoader::Loading_For_Tool_Level()
{
	_matrix		PivotMatrix;

// 	PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
// 	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL::LEVEL_TOOL, TEXT("Prototype_Component_Model_Raider"),
// 		CModel::Create(m_pDevice, m_pContext, CModel::TYPE::TYPE_NONANIM, "../Bin/Resources/Models/King/King.fbx", PivotMatrix))))
// 		return E_FAIL;


	if (E_FAIL == Loading_For_Level<CTerrain_MapTool, CVIBuffer_Dynamic_Terrain>(LEVEL::LEVEL_TOOL))
		return E_FAIL;

// 	/* For.Prototype_GameObject_Raider */
// 	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Raider"),
// 		CRaider::Create(m_pDevice, m_pContext))))
// 		return E_FAIL;

	return S_OK;
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
