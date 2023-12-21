#include "..\Public\King_GamePlay.h"

CKing_GamePlay::CKing_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CKing(pDevice, pContext)
{
}

CKing_GamePlay::CKing_GamePlay(const CKing_GamePlay& rhs)
	: CKing(rhs)
{
}

HRESULT CKing_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_GAMEPLAY)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_King_GamePlay"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}

CKing_GamePlay* CKing_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CKing_GamePlay* pInstance = new CKing_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CKing_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CKing_GamePlay* CKing_GamePlay::Clone(void* pArg)
{
	CKing_GamePlay* pInstance = new CKing_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CKing_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CKing_GamePlay::Free()
{
	__super::Free();
}
