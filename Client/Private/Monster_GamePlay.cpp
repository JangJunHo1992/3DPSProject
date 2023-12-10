#include "..\Public\Monster_GamePlay.h"

CMonster_GamePlay::CMonster_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CMonster(pDevice, pContext)
{
}

CMonster_GamePlay::CMonster_GamePlay(const CMonster_GamePlay& rhs)
	: CMonster(rhs)
{
}

HRESULT CMonster_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin()))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Fiona_GamePlay"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}


CMonster_GamePlay* CMonster_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CMonster_GamePlay* pInstance = new CMonster_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CMonster_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CMonster_GamePlay* CMonster_GamePlay::Clone(void* pArg)
{
	CMonster_GamePlay* pInstance = new CMonster_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CMonster_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMonster_GamePlay::Free()
{
	__super::Free();
}

