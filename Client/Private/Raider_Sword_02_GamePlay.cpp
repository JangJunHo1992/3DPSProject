#include "..\Public\Raider_Sword_02_GamePlay.h"


CRaider_Sword_02_GamePlay::CRaider_Sword_02_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CRaider_Weapon(pDevice, pContext)
{
}

CRaider_Sword_02_GamePlay::CRaider_Sword_02_GamePlay(const CRaider_Sword_02_GamePlay& rhs)
	: CRaider_Weapon(rhs)
{
}

HRESULT CRaider_Sword_02_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_GAMEPLAY)))
		return E_FAIL;

	return S_OK;
}

HRESULT CRaider_Sword_02_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CRaider_Sword_02_GamePlay* CRaider_Sword_02_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CRaider_Sword_02_GamePlay* pInstance = new CRaider_Sword_02_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CRaider_Sword_02_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CRaider_Sword_02_GamePlay::Clone(void* pArg)
{
	CRaider_Sword_02_GamePlay* pInstance = new CRaider_Sword_02_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CRaider_Sword_02_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CRaider_Sword_02_GamePlay::Free()
{
	__super::Free();
}
