#include "..\Public\Raider_Body_Tool.h"


CRaider_Body_Tool::CRaider_Body_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CRaider_Body(pDevice, pContext)
{
}

CRaider_Body_Tool::CRaider_Body_Tool(const CRaider_Body_Tool& rhs)
	: CRaider_Body(rhs)
{
}

HRESULT CRaider_Body_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}

HRESULT CRaider_Body_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CRaider_Body_Tool* CRaider_Body_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CRaider_Body_Tool* pInstance = new CRaider_Body_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CRaider_Body_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CRaider_Body_Tool::Clone(void* pArg)
{
	CRaider_Body_Tool* pInstance = new CRaider_Body_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CRaider_Body_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CRaider_Body_Tool::Free()
{
	__super::Free();
}
