#include "Magician_Body_Tool.h"


CMagician_Body_Tool::CMagician_Body_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CMagician_Body(pDevice, pContext)
{
}

CMagician_Body_Tool::CMagician_Body_Tool(const CMagician_Body_Tool& rhs)
	: CMagician_Body(rhs)
{
}

HRESULT CMagician_Body_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}

HRESULT CMagician_Body_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CMagician_Body_Tool* CMagician_Body_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CMagician_Body_Tool* pInstance = new CMagician_Body_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CMagician_Body_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CMagician_Body_Tool::Clone(void* pArg)
{
	CMagician_Body_Tool* pInstance = new CMagician_Body_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CMagician_Body_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMagician_Body_Tool::Free()
{
	__super::Free();
}
