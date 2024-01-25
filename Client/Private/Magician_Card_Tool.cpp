#include "Magician_Card_Tool.h"


CMagician_Card_Tool::CMagician_Card_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CMagician_Card(pDevice, pContext)
{
}

CMagician_Card_Tool::CMagician_Card_Tool(const CMagician_Card_Tool& rhs)
	: CMagician_Card(rhs)
{
}

HRESULT CMagician_Card_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}

HRESULT CMagician_Card_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CMagician_Card_Tool* CMagician_Card_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CMagician_Card_Tool* pInstance = new CMagician_Card_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CMagician_Card_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CMagician_Card_Tool::Clone(void* pArg)
{
	CMagician_Card_Tool* pInstance = new CMagician_Card_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CMagician_Card_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMagician_Card_Tool::Free()
{
	__super::Free();
}
