#include "Varg_Body_Tool.h"


CVarg_Body_Tool::CVarg_Body_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CVarg_Body(pDevice, pContext)
{
}

CVarg_Body_Tool::CVarg_Body_Tool(const CVarg_Body_Tool& rhs)
	: CVarg_Body(rhs)
{
}

HRESULT CVarg_Body_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}

HRESULT CVarg_Body_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CVarg_Body_Tool* CVarg_Body_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CVarg_Body_Tool* pInstance = new CVarg_Body_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CVarg_Body_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CVarg_Body_Tool::Clone(void* pArg)
{
	CVarg_Body_Tool* pInstance = new CVarg_Body_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CVarg_Body_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CVarg_Body_Tool::Free()
{
	__super::Free();
}
