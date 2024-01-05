#include "Covus_Body_Tool.h"


CCovus_Body_Tool::CCovus_Body_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CCovus_Body(pDevice, pContext)
{
}

CCovus_Body_Tool::CCovus_Body_Tool(const CCovus_Body_Tool& rhs)
	: CCovus_Body(rhs)
{
}

HRESULT CCovus_Body_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}

HRESULT CCovus_Body_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CCovus_Body_Tool* CCovus_Body_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CCovus_Body_Tool* pInstance = new CCovus_Body_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CCovus_Body_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CCovus_Body_Tool::Clone(void* pArg)
{
	CCovus_Body_Tool* pInstance = new CCovus_Body_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CCovus_Body_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCovus_Body_Tool::Free()
{
	__super::Free();
}
