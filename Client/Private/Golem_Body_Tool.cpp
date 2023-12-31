#include "..\Public\Golem_Body_Tool.h"


CGolem_Body_Tool::CGolem_Body_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGolem_Body(pDevice, pContext)
{
}

CGolem_Body_Tool::CGolem_Body_Tool(const CGolem_Body_Tool& rhs)
	: CGolem_Body(rhs)
{
}

HRESULT CGolem_Body_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}

HRESULT CGolem_Body_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CGolem_Body_Tool* CGolem_Body_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CGolem_Body_Tool* pInstance = new CGolem_Body_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CGolem_Body_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CGolem_Body_Tool::Clone(void* pArg)
{
	CGolem_Body_Tool* pInstance = new CGolem_Body_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CGolem_Body_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CGolem_Body_Tool::Free()
{
	__super::Free();
}
