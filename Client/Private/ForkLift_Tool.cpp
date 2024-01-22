#include "..\Public\ForkLift_Tool.h"
#include "GameInstance.h"

CForkLift_Tool::CForkLift_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CForkLift(pDevice, pContext)
{
}

CForkLift_Tool::CForkLift_Tool(const CForkLift_Tool& rhs)
	: CForkLift(rhs)
{
}

HRESULT CForkLift_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	return S_OK;
}

HRESULT CForkLift_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL_TOOL)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(LEVEL_TOOL, TEXT("Prototype_Component_Model_ForkLift"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}

_bool CForkLift_Tool::Pick(_float3* out)
{
	RAY ray = m_pGameInstance->Get_MouseRayLocal(g_hWnd, g_iWinSizeX, g_iWinSizeY, m_pTransformCom->Get_WorldMatrix());
	vector<class CMesh*>* meshes = m_pModelCom->Get_Meshes();
	return m_pGameInstance->Picking_Mesh(ray, out, meshes);
}

CForkLift_Tool* CForkLift_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CForkLift_Tool* pInstance = new CForkLift_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CForkLift_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CForkLift_Tool* CForkLift_Tool::Clone(void* pArg)
{
	CForkLift_Tool* pInstance = new CForkLift_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CForkLift_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CForkLift_Tool::Free()
{
	__super::Free();
	Safe_Release(m_pGameInstance);
}
