#include "..\Public\DarkKnight_Body_GamePlay.h"


CDarkKnight_Body_GamePlay::CDarkKnight_Body_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CDarkKnight_Body(pDevice, pContext)
{
}

CDarkKnight_Body_GamePlay::CDarkKnight_Body_GamePlay(const CDarkKnight_Body_GamePlay& rhs)
	: CDarkKnight_Body(rhs)
{
}

HRESULT CDarkKnight_Body_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_GAMEPLAY)))
		return E_FAIL;

	return S_OK;
}

HRESULT CDarkKnight_Body_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CDarkKnight_Body_GamePlay* CDarkKnight_Body_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CDarkKnight_Body_GamePlay* pInstance = new CDarkKnight_Body_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CDarkKnight_Body_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CDarkKnight_Body_GamePlay::Clone(void* pArg)
{
	CDarkKnight_Body_GamePlay* pInstance = new CDarkKnight_Body_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CDarkKnight_Body_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CDarkKnight_Body_GamePlay::Free()
{
	__super::Free();
}
