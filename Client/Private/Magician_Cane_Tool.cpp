#include "Magician_Cane_Tool.h"


CMagician_Cane_Tool::CMagician_Cane_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CMagician_Cane(pDevice, pContext)
{
}

CMagician_Cane_Tool::CMagician_Cane_Tool(const CMagician_Cane_Tool& rhs)
	: CMagician_Cane(rhs)
{
}

HRESULT CMagician_Cane_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}

HRESULT CMagician_Cane_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CMagician_Cane_Tool* CMagician_Cane_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CMagician_Cane_Tool* pInstance = new CMagician_Cane_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CMagician_Cane_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CMagician_Cane_Tool::Clone(void* pArg)
{
	CMagician_Cane_Tool* pInstance = new CMagician_Cane_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CMagician_Cane_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMagician_Cane_Tool::Free()
{
	__super::Free();
}
