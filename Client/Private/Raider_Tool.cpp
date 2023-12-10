#include "..\Public\Raider_Tool.h"
#include "GameInstance.h"

CRaider_Tool::CRaider_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CRaider(pDevice, pContext)
{
}

CRaider_Tool::CRaider_Tool(const CRaider_Tool& rhs)
	: CRaider(rhs)
{
}

HRESULT CRaider_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	return S_OK;
}

_bool CRaider_Tool::Pick(_float3* out)
{

	RAY ray = m_pGameInstance->Get_MouseRayLocal(g_hWnd, g_iWinSizeX, g_iWinSizeY, m_pTransformCom->Get_WorldMatrix());
	vector<class CMesh*>* meshes = m_pModelCom->Get_Meshes();
	return m_pGameInstance->Picking_Mesh(ray, out, meshes);
}

HRESULT CRaider_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin()))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::Add_Component(LEVEL_TOOL, TEXT("Prototype_Component_Model_Raider_Tool"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}



CRaider_Tool* CRaider_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CRaider_Tool* pInstance = new CRaider_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CRaider_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CRaider_Tool* CRaider_Tool::Clone(void* pArg)
{
	CRaider_Tool* pInstance = new CRaider_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CRaider_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CRaider_Tool::Free()
{
	__super::Free();
	Safe_Release(m_pGameInstance);
}
