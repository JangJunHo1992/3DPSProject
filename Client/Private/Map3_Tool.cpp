#include "..\Public\Map3_Tool.h"
#include "GameInstance.h"

CMap3_Tool::CMap3_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CMap3(pDevice, pContext)
{
}

CMap3_Tool::CMap3_Tool(const CMap3_Tool& rhs)
	: CMap3(rhs)
{
}

HRESULT CMap3_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	return S_OK;
}

HRESULT CMap3_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL_TOOL)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(LEVEL_TOOL, TEXT("Prototype_Component_Model_Map3"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}

_bool CMap3_Tool::Pick(_float3* out)
{
	RAY ray = m_pGameInstance->Get_MouseRayLocal(g_hWnd, g_iWinSizeX, g_iWinSizeY, m_pTransformCom->Get_WorldMatrix());
	vector<class CMesh*>* meshes = m_pModelCom->Get_Meshes();
	return m_pGameInstance->Picking_Mesh(ray, out, meshes);
}

CMap3_Tool* CMap3_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CMap3_Tool* pInstance = new CMap3_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CMap3_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CMap3_Tool* CMap3_Tool::Clone(void* pArg)
{
	CMap3_Tool* pInstance = new CMap3_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CMap3_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMap3_Tool::Free()
{
	__super::Free();
	Safe_Release(m_pGameInstance);
}
