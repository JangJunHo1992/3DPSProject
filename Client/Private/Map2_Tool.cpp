#include "..\Public\Map2_Tool.h"
#include "GameInstance.h"

CMap2_Tool::CMap2_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CMap2(pDevice, pContext)
{
}

CMap2_Tool::CMap2_Tool(const CMap2_Tool& rhs)
	: CMap2(rhs)
{
}

HRESULT CMap2_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	return S_OK;
}

HRESULT CMap2_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL_TOOL)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(LEVEL_TOOL, TEXT("Prototype_Component_Model_Map2"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}

_bool CMap2_Tool::Pick(_float3* out)
{
	RAY ray = m_pGameInstance->Get_MouseRayLocal(g_hWnd, g_iWinSizeX, g_iWinSizeY, m_pTransformCom->Get_WorldMatrix());
	vector<class CMesh*>* meshes = m_pModelCom->Get_Meshes();
	return m_pGameInstance->Picking_Mesh(ray, out, meshes);
}

CMap2_Tool* CMap2_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CMap2_Tool* pInstance = new CMap2_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CMap2_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CMap2_Tool* CMap2_Tool::Clone(void* pArg)
{
	CMap2_Tool* pInstance = new CMap2_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CMap2_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMap2_Tool::Free()
{
	__super::Free();
	Safe_Release(m_pGameInstance);
}
