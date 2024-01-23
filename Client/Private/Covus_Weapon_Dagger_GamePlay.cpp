#include "Covus_Weapon_Dagger_GamePlay.h"
#include "GameInstance.h"


CCovus_Weapon_Dagger_GamePlay::CCovus_Weapon_Dagger_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CCovus_Weapon_Dagger(pDevice, pContext)
{
}

CCovus_Weapon_Dagger_GamePlay::CCovus_Weapon_Dagger_GamePlay(const CCovus_Weapon_Dagger_GamePlay& rhs)
	: CCovus_Weapon_Dagger(rhs)
{
}

HRESULT CCovus_Weapon_Dagger_GamePlay::Ready_Components()
{
	switch (m_pGameInstance->Get_NextLevel())
	{
	case 2:
		if (FAILED(Ready_Components_Origin(LEVEL_GAMEPLAY)))
			return E_FAIL;
		break;
	case 6:
		if (FAILED(Ready_Components_Origin(LEVEL_BOSS1)))
			return E_FAIL;
		break;
	case 7:
		if (FAILED(Ready_Components_Origin(LEVEL_BOSS2)))
			return E_FAIL;
		break;
	default:
		break;
	}

	return S_OK;
}

HRESULT CCovus_Weapon_Dagger_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CCovus_Weapon_Dagger_GamePlay* CCovus_Weapon_Dagger_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CCovus_Weapon_Dagger_GamePlay* pInstance = new CCovus_Weapon_Dagger_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CCovus_Weapon_Dagger_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CCovus_Weapon_Dagger_GamePlay::Clone(void* pArg)
{
	CCovus_Weapon_Dagger_GamePlay* pInstance = new CCovus_Weapon_Dagger_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CCovus_Weapon_Dagger_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCovus_Weapon_Dagger_GamePlay::Free()
{
	__super::Free();
}
