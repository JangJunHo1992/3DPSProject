#include "..\Public\King_Tool.h"
#include "GameInstance.h"

CKing_Tool::CKing_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CKing(pDevice, pContext)
{
}

CKing_Tool::CKing_Tool(const CKing_Tool& rhs)
	: CKing(rhs)
{
}

HRESULT CKing_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	return S_OK;
}

_bool CKing_Tool::Pick(_float3* out)
{

	RAY ray = m_pGameInstance->Get_MouseRayLocal(g_hWnd, g_iWinSizeX, g_iWinSizeY, m_pTransformCom->Get_WorldMatrix());
	vector<class CMesh*>* meshes = m_pModelCom->Get_Meshes();
	return m_pGameInstance->Picking_Mesh(ray, out, meshes);
}

HRESULT CKing_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::Add_Component(LEVEL_TOOL, TEXT("Prototype_Component_Model_King_Tool"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}



CKing_Tool* CKing_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CKing_Tool* pInstance = new CKing_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CKing_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CKing_Tool* CKing_Tool::Clone(void* pArg)
{
	CKing_Tool* pInstance = new CKing_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CKing_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CKing_Tool::Free()
{
	__super::Free();
	Safe_Release(m_pGameInstance);
}
