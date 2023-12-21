#include "..\Public\KnightGuard_Tool.h"
#include "GameInstance.h"

CKnightGuard_Tool::CKnightGuard_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CKnightGuard(pDevice, pContext)
{
}

CKnightGuard_Tool::CKnightGuard_Tool(const CKnightGuard_Tool& rhs)
	: CKnightGuard(rhs)
{
}

HRESULT CKnightGuard_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	return S_OK;
}

_bool CKnightGuard_Tool::Pick(_float3* out)
{

	RAY ray = m_pGameInstance->Get_MouseRayLocal(g_hWnd, g_iWinSizeX, g_iWinSizeY, m_pTransformCom->Get_WorldMatrix());
	vector<class CMesh*>* meshes = m_pModelCom->Get_Meshes();
	return m_pGameInstance->Picking_Mesh(ray, out, meshes);
}

HRESULT CKnightGuard_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::Add_Component(LEVEL_TOOL, TEXT("Prototype_Component_Model_KnightGuard_Tool"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}



CKnightGuard_Tool* CKnightGuard_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CKnightGuard_Tool* pInstance = new CKnightGuard_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CKnightGuard_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CKnightGuard_Tool* CKnightGuard_Tool::Clone(void* pArg)
{
	CKnightGuard_Tool* pInstance = new CKnightGuard_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CKnightGuard_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CKnightGuard_Tool::Free()
{
	__super::Free();
	Safe_Release(m_pGameInstance);
}
