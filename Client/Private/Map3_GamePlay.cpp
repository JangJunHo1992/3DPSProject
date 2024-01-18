#include "..\Public\Map3_GamePlay.h"

CMap3_GamePlay::CMap3_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CMap3(pDevice, pContext)
{
}

CMap3_GamePlay::CMap3_GamePlay(const CMap3_GamePlay& rhs)
	: CMap3(rhs)
{
}

HRESULT CMap3_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL_BOSS2)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(LEVEL_BOSS2, TEXT("Prototype_Component_Model_Map3"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}

CMap3_GamePlay* CMap3_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CMap3_GamePlay* pInstance = new CMap3_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CMap3_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CMap3_GamePlay* CMap3_GamePlay::Clone(void* pArg)
{
	CMap3_GamePlay* pInstance = new CMap3_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CMap3");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMap3_GamePlay::Free()
{
	__super::Free();
}
