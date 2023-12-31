#include "..\Public\Wizard_Body_GamePlay.h"


CWizard_Body_GamePlay::CWizard_Body_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CWizard_Body(pDevice, pContext)
{
}

CWizard_Body_GamePlay::CWizard_Body_GamePlay(const CWizard_Body_GamePlay& rhs)
	: CWizard_Body(rhs)
{
}

HRESULT CWizard_Body_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_GAMEPLAY)))
		return E_FAIL;

	return S_OK;
}

HRESULT CWizard_Body_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CWizard_Body_GamePlay* CWizard_Body_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CWizard_Body_GamePlay* pInstance = new CWizard_Body_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CWizard_Body_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CWizard_Body_GamePlay::Clone(void* pArg)
{
	CWizard_Body_GamePlay* pInstance = new CWizard_Body_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CWizard_Body_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CWizard_Body_GamePlay::Free()
{
	__super::Free();
}
