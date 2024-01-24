#include "JobMob1_Weapon_GamePlay.h"
#include "GameInstance.h"

CJobMob1_Weapon_GamePlay::CJobMob1_Weapon_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CJobMob1_Weapon(pDevice, pContext)
{
}

CJobMob1_Weapon_GamePlay::CJobMob1_Weapon_GamePlay(const CJobMob1_Weapon_GamePlay& rhs)
	: CJobMob1_Weapon(rhs)
{
}

HRESULT CJobMob1_Weapon_GamePlay::Ready_Components()
{
	m_pGameInstance->Get_NextLevel();
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

HRESULT CJobMob1_Weapon_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CJobMob1_Weapon_GamePlay* CJobMob1_Weapon_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CJobMob1_Weapon_GamePlay* pInstance = new CJobMob1_Weapon_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CJobMob1_Weapon_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CJobMob1_Weapon_GamePlay::Clone(void* pArg)
{
	CJobMob1_Weapon_GamePlay* pInstance = new CJobMob1_Weapon_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CJobMob1_Weapon_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CJobMob1_Weapon_GamePlay::Free()
{
	__super::Free();
}
