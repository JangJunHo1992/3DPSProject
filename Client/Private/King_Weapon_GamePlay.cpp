#include "..\Public\King_Weapon_GamePlay.h"


CKing_Weapon_GamePlay::CKing_Weapon_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CKing_Weapon(pDevice, pContext)
{
}

CKing_Weapon_GamePlay::CKing_Weapon_GamePlay(const CKing_Weapon_GamePlay& rhs)
	: CKing_Weapon(rhs)
{
}

HRESULT CKing_Weapon_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_GAMEPLAY)))
		return E_FAIL;

	return S_OK;
}

HRESULT CKing_Weapon_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CKing_Weapon_GamePlay* CKing_Weapon_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CKing_Weapon_GamePlay* pInstance = new CKing_Weapon_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CKing_Weapon_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CKing_Weapon_GamePlay::Clone(void* pArg)
{
	CKing_Weapon_GamePlay* pInstance = new CKing_Weapon_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CKing_Weapon_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CKing_Weapon_GamePlay::Free()
{
	__super::Free();
}
