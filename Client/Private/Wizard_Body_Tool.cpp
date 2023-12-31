#include "..\Public\Wizard_Body_Tool.h"


CWizard_Body_Tool::CWizard_Body_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CWizard_Body(pDevice, pContext)
{
}

CWizard_Body_Tool::CWizard_Body_Tool(const CWizard_Body_Tool& rhs)
	: CWizard_Body(rhs)
{
}

HRESULT CWizard_Body_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}

HRESULT CWizard_Body_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CWizard_Body_Tool* CWizard_Body_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CWizard_Body_Tool* pInstance = new CWizard_Body_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CWizard_Body_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CWizard_Body_Tool::Clone(void* pArg)
{
	CWizard_Body_Tool* pInstance = new CWizard_Body_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CWizard_Body_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CWizard_Body_Tool::Free()
{
	__super::Free();
}
