#include "..\Public\Raider_Body_GamePlay.h"


CRaider_Body_GamePlay::CRaider_Body_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CRaider_Body(pDevice, pContext)
{
}

CRaider_Body_GamePlay::CRaider_Body_GamePlay(const CRaider_Body_GamePlay& rhs)
	: CRaider_Body(rhs)
{
}

HRESULT CRaider_Body_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_GAMEPLAY)))
		return E_FAIL;

	return S_OK;
}

HRESULT CRaider_Body_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CRaider_Body_GamePlay* CRaider_Body_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CRaider_Body_GamePlay* pInstance = new CRaider_Body_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CRaider_Body_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CRaider_Body_GamePlay::Clone(void* pArg)
{
	CRaider_Body_GamePlay* pInstance = new CRaider_Body_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CRaider_Body_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CRaider_Body_GamePlay::Free()
{
	__super::Free();
}
