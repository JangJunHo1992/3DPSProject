#include "..\Public\Map2_GamePlay.h"

CMap2_GamePlay::CMap2_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CMap2(pDevice, pContext)
{
}

CMap2_GamePlay::CMap2_GamePlay(const CMap2_GamePlay& rhs)
	: CMap2(rhs)
{
}

HRESULT CMap2_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL_BOSS1)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(LEVEL_BOSS1, TEXT("Prototype_Component_Model_Map2"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}

CMap2_GamePlay* CMap2_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CMap2_GamePlay* pInstance = new CMap2_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CMap2_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CMap2_GamePlay* CMap2_GamePlay::Clone(void* pArg)
{
	CMap2_GamePlay* pInstance = new CMap2_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CMap2");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMap2_GamePlay::Free()
{
	__super::Free();
}
