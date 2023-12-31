#include "..\Public\King_Body_GamePlay.h"


CKing_Body_GamePlay::CKing_Body_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CKing_Body(pDevice, pContext)
{
}

CKing_Body_GamePlay::CKing_Body_GamePlay(const CKing_Body_GamePlay& rhs)
	: CKing_Body(rhs)
{
}

HRESULT CKing_Body_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_GAMEPLAY)))
		return E_FAIL;

	return S_OK;
}

HRESULT CKing_Body_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CKing_Body_GamePlay* CKing_Body_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CKing_Body_GamePlay* pInstance = new CKing_Body_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CKing_Body_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CKing_Body_GamePlay::Clone(void* pArg)
{
	CKing_Body_GamePlay* pInstance = new CKing_Body_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CKing_Body_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CKing_Body_GamePlay::Free()
{
	__super::Free();
}
