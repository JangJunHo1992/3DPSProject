#include "..\Public\Raider_GamePlay.h"

CRaider_GamePlay::CRaider_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CRaider(pDevice, pContext)
{
}

CRaider_GamePlay::CRaider_GamePlay(const CRaider_GamePlay& rhs)
	: CRaider(rhs)
{
}

HRESULT CRaider_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin()))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Raider_GamePlay"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}

CRaider_GamePlay* CRaider_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CRaider_GamePlay* pInstance = new CRaider_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CRaider_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CRaider_GamePlay* CRaider_GamePlay::Clone(void* pArg)
{
	CRaider_GamePlay* pInstance = new CRaider_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CRaider_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CRaider_GamePlay::Free()
{
	__super::Free();
}
