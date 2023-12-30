#include "..\Public\DarkKnight_Body_Tool.h"


CDarkKnight_Body_Tool::CDarkKnight_Body_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CDarkKnight_Body(pDevice, pContext)
{
}

CDarkKnight_Body_Tool::CDarkKnight_Body_Tool(const CDarkKnight_Body_Tool& rhs)
	: CDarkKnight_Body(rhs)
{
}

HRESULT CDarkKnight_Body_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	return S_OK;
}

HRESULT CDarkKnight_Body_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CDarkKnight_Body_Tool* CDarkKnight_Body_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CDarkKnight_Body_Tool* pInstance = new CDarkKnight_Body_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CDarkKnight_Body_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CDarkKnight_Body_Tool::Clone(void* pArg)
{
	CDarkKnight_Body_Tool* pInstance = new CDarkKnight_Body_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CDarkKnight_Body_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CDarkKnight_Body_Tool::Free()
{
	__super::Free();
}
