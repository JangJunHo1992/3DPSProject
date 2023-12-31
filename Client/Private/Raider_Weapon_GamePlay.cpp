#include "..\Public\Raider_Weapon_GamePlay.h"


CRaider_Weapon_GamePlay::CRaider_Weapon_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CRaider_Weapon(pDevice, pContext)
{
}

CRaider_Weapon_GamePlay::CRaider_Weapon_GamePlay(const CRaider_Weapon_GamePlay& rhs)
	: CRaider_Weapon(rhs)
{
}

HRESULT CRaider_Weapon_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_GAMEPLAY)))
		return E_FAIL;

	return S_OK;
}

HRESULT CRaider_Weapon_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CRaider_Weapon_GamePlay* CRaider_Weapon_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CRaider_Weapon_GamePlay* pInstance = new CRaider_Weapon_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CRaider_Weapon_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CRaider_Weapon_GamePlay::Clone(void* pArg)
{
	CRaider_Weapon_GamePlay* pInstance = new CRaider_Weapon_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CRaider_Weapon_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CRaider_Weapon_GamePlay::Free()
{
	__super::Free();
}
