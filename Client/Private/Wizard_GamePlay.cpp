#include "..\Public\Wizard_GamePlay.h"

CWizard_GamePlay::CWizard_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CWizard(pDevice, pContext)
{
}

CWizard_GamePlay::CWizard_GamePlay(const CWizard_GamePlay& rhs)
	: CWizard(rhs)
{
}

HRESULT CWizard_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_GAMEPLAY)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Wizard_GamePlay"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}

CWizard_GamePlay* CWizard_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CWizard_GamePlay* pInstance = new CWizard_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CWizard_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CWizard_GamePlay* CWizard_GamePlay::Clone(void* pArg)
{
	CWizard_GamePlay* pInstance = new CWizard_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CWizard_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CWizard_GamePlay::Free()
{
	__super::Free();
}
