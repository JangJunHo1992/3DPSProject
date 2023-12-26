#include "..\Public\DarkKnight_Tool.h"
#include "GameInstance.h"

CDarkKnight_Tool::CDarkKnight_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CDarkKnight(pDevice, pContext)
{
}

CDarkKnight_Tool::CDarkKnight_Tool(const CDarkKnight_Tool& rhs)
	: CDarkKnight(rhs)
{
}

HRESULT CDarkKnight_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	return S_OK;
}

_bool CDarkKnight_Tool::Pick(_float3* out)
{

	RAY ray = m_pGameInstance->Get_MouseRayLocal(g_hWnd, g_iWinSizeX, g_iWinSizeY, m_pTransformCom->Get_WorldMatrix());
	vector<class CMesh*>* meshes = m_pModelCom->Get_Meshes();
	return m_pGameInstance->Picking_Mesh(ray, out, meshes);
}

HRESULT CDarkKnight_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::Add_Component(LEVEL_TOOL, TEXT("Prototype_Component_Model_DarkKnight_Tool"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}



CDarkKnight_Tool* CDarkKnight_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CDarkKnight_Tool* pInstance = new CDarkKnight_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CDarkKnight_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CDarkKnight_Tool* CDarkKnight_Tool::Clone(void* pArg)
{
	CDarkKnight_Tool* pInstance = new CDarkKnight_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CDarkKnight_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CDarkKnight_Tool::Free()
{
	__super::Free();
	Safe_Release(m_pGameInstance);
}
