#include "..\Public\Golem_Tool.h"
#include "GameInstance.h"

CGolem_Tool::CGolem_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGolem(pDevice, pContext)
{
}

CGolem_Tool::CGolem_Tool(const CGolem_Tool& rhs)
	: CGolem(rhs)
{
}

HRESULT CGolem_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	return S_OK;
}

_bool CGolem_Tool::Pick(_float3* out)
{

	RAY ray = m_pGameInstance->Get_MouseRayLocal(g_hWnd, g_iWinSizeX, g_iWinSizeY, m_pTransformCom->Get_WorldMatrix());
	vector<class CMesh*>* meshes = m_pModelCom->Get_Meshes();
	return m_pGameInstance->Picking_Mesh(ray, out, meshes);
}

HRESULT CGolem_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::Add_Component(LEVEL_TOOL, TEXT("Prototype_Component_Model_Golem_Tool"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}



CGolem_Tool* CGolem_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CGolem_Tool* pInstance = new CGolem_Tool(pDevice, pContext);

	/* ������ü�� �ʱ�ȭ�Ѵ�.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CGolem_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGolem_Tool* CGolem_Tool::Clone(void* pArg)
{
	CGolem_Tool* pInstance = new CGolem_Tool(*this);

	/* ������ü�� �ʱ�ȭ�Ѵ�.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CGolem_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CGolem_Tool::Free()
{
	__super::Free();
	Safe_Release(m_pGameInstance);
}
