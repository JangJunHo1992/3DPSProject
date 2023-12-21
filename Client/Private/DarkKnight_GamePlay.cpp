#include "..\Public\DarkKnight_GamePlay.h"

CDarkKnight_GamePlay::CDarkKnight_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CDarkKnight(pDevice, pContext)
{
}

CDarkKnight_GamePlay::CDarkKnight_GamePlay(const CDarkKnight_GamePlay& rhs)
	: CDarkKnight(rhs)
{
}

HRESULT CDarkKnight_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_GAMEPLAY)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_DarkKnight_GamePlay"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}

CDarkKnight_GamePlay* CDarkKnight_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CDarkKnight_GamePlay* pInstance = new CDarkKnight_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CDarkKnight_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CDarkKnight_GamePlay* CDarkKnight_GamePlay::Clone(void* pArg)
{
	CDarkKnight_GamePlay* pInstance = new CDarkKnight_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CDarkKnight_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CDarkKnight_GamePlay::Free()
{
	__super::Free();
}
