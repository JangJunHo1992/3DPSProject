#include "..\Public\Golem_GamePlay.h"

CGolem_GamePlay::CGolem_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGolem(pDevice, pContext)
{
}

CGolem_GamePlay::CGolem_GamePlay(const CGolem_GamePlay& rhs)
	: CGolem(rhs)
{
}

HRESULT CGolem_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_GAMEPLAY)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Golem_GamePlay"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}

CGolem_GamePlay* CGolem_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CGolem_GamePlay* pInstance = new CGolem_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CGolem_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGolem_GamePlay* CGolem_GamePlay::Clone(void* pArg)
{
	CGolem_GamePlay* pInstance = new CGolem_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CGolem_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CGolem_GamePlay::Free()
{
	__super::Free();
}
