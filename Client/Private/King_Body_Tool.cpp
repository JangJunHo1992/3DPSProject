#include "..\Public\King_Body_Tool.h"


CKing_Body_Tool::CKing_Body_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CKing_Body(pDevice, pContext)
{
}

CKing_Body_Tool::CKing_Body_Tool(const CKing_Body_Tool& rhs)
	: CKing_Body(rhs)
{
}

HRESULT CKing_Body_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}

HRESULT CKing_Body_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CKing_Body_Tool* CKing_Body_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CKing_Body_Tool* pInstance = new CKing_Body_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CKing_Body_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CKing_Body_Tool::Clone(void* pArg)
{
	CKing_Body_Tool* pInstance = new CKing_Body_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CKing_Body_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CKing_Body_Tool::Free()
{
	__super::Free();
}
