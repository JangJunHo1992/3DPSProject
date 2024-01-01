#include "..\Public\KnightGuard_Body_Tool.h"


CKnightGuard_Body_Tool::CKnightGuard_Body_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CKnightGuard_Body(pDevice, pContext)
{
}

CKnightGuard_Body_Tool::CKnightGuard_Body_Tool(const CKnightGuard_Body_Tool& rhs)
	: CKnightGuard_Body(rhs)
{
}

HRESULT CKnightGuard_Body_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}

HRESULT CKnightGuard_Body_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CKnightGuard_Body_Tool* CKnightGuard_Body_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CKnightGuard_Body_Tool* pInstance = new CKnightGuard_Body_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CKnightGuard_Body_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CKnightGuard_Body_Tool::Clone(void* pArg)
{
	CKnightGuard_Body_Tool* pInstance = new CKnightGuard_Body_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CKnightGuard_Body_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CKnightGuard_Body_Tool::Free()
{
	__super::Free();
}
