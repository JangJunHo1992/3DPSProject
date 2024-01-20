#include "..\Public\KnightGuard_GamePlay.h"

CKnightGuard_GamePlay::CKnightGuard_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CKnightGuard(pDevice, pContext)
{
}

CKnightGuard_GamePlay::CKnightGuard_GamePlay(const CKnightGuard_GamePlay& rhs)
	: CKnightGuard(rhs)
{
}

HRESULT CKnightGuard_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_GAMEPLAY)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_KnightGuard_GamePlay"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}

CKnightGuard_GamePlay* CKnightGuard_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CKnightGuard_GamePlay* pInstance = new CKnightGuard_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CKnightGuard_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CKnightGuard_GamePlay* CKnightGuard_GamePlay::Clone(void* pArg)
{
	CKnightGuard_GamePlay* pInstance = new CKnightGuard_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CKnightGuard_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CKnightGuard_GamePlay::Free()
{
	__super::Free();
}
