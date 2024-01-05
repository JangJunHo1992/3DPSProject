#include "Covus_Weapon_GamePlay.h"


CCovus_Weapon_GamePlay::CCovus_Weapon_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CCovus_Weapon(pDevice, pContext)
{
}

CCovus_Weapon_GamePlay::CCovus_Weapon_GamePlay(const CCovus_Weapon_GamePlay& rhs)
	: CCovus_Weapon(rhs)
{
}

HRESULT CCovus_Weapon_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_GAMEPLAY)))
		return E_FAIL;

	return S_OK;
}

HRESULT CCovus_Weapon_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CCovus_Weapon_GamePlay* CCovus_Weapon_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CCovus_Weapon_GamePlay* pInstance = new CCovus_Weapon_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CCovus_Weapon_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CCovus_Weapon_GamePlay::Clone(void* pArg)
{
	CCovus_Weapon_GamePlay* pInstance = new CCovus_Weapon_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CCovus_Weapon_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCovus_Weapon_GamePlay::Free()
{
	__super::Free();
}
