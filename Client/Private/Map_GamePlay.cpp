#include "..\Public\Map_GamePlay.h"

CMap_GamePlay::CMap_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CMap(pDevice, pContext)
{
}

CMap_GamePlay::CMap_GamePlay(const CMap_GamePlay& rhs)
	: CMap(rhs)
{
}

HRESULT CMap_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL_GAMEPLAY)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Map"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}

CMap_GamePlay* CMap_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CMap_GamePlay* pInstance = new CMap_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CMap_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CMap_GamePlay* CMap_GamePlay::Clone(void* pArg)
{
	CMap_GamePlay* pInstance = new CMap_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CMap");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMap_GamePlay::Free()
{
	__super::Free();
}
