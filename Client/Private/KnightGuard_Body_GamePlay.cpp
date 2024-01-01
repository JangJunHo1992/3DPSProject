#include "..\Public\KnightGuard_Body_GamePlay.h"


CKnightGuard_Body_GamePlay::CKnightGuard_Body_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CKnightGuard_Body(pDevice, pContext)
{
}

CKnightGuard_Body_GamePlay::CKnightGuard_Body_GamePlay(const CKnightGuard_Body_GamePlay& rhs)
	: CKnightGuard_Body(rhs)
{
}

HRESULT CKnightGuard_Body_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_GAMEPLAY)))
		return E_FAIL;

	return S_OK;
}

HRESULT CKnightGuard_Body_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CKnightGuard_Body_GamePlay* CKnightGuard_Body_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CKnightGuard_Body_GamePlay* pInstance = new CKnightGuard_Body_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CKnightGuard_Body_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CKnightGuard_Body_GamePlay::Clone(void* pArg)
{
	CKnightGuard_Body_GamePlay* pInstance = new CKnightGuard_Body_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CKnightGuard_Body_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CKnightGuard_Body_GamePlay::Free()
{
	__super::Free();
}
