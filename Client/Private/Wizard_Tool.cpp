#include "..\Public\Wizard_Tool.h"
#include "GameInstance.h"

CWizard_Tool::CWizard_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CWizard(pDevice, pContext)
{
}

CWizard_Tool::CWizard_Tool(const CWizard_Tool& rhs)
	: CWizard(rhs)
{
}

HRESULT CWizard_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	return S_OK;
}

_bool CWizard_Tool::Pick(_float3* out)
{

	RAY ray = m_pGameInstance->Get_MouseRayLocal(g_hWnd, g_iWinSizeX, g_iWinSizeY, m_pTransformCom->Get_WorldMatrix());
	vector<class CMesh*>* meshes = m_pModelCom->Get_Meshes();
	return m_pGameInstance->Picking_Mesh(ray, out, meshes);
}

HRESULT CWizard_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::Add_Component(LEVEL_TOOL, TEXT("Prototype_Component_Model_Wizard_Tool"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}



CWizard_Tool* CWizard_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CWizard_Tool* pInstance = new CWizard_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CWizard_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CWizard_Tool* CWizard_Tool::Clone(void* pArg)
{
	CWizard_Tool* pInstance = new CWizard_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CWizard_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CWizard_Tool::Free()
{
	__super::Free();
	Safe_Release(m_pGameInstance);
}
