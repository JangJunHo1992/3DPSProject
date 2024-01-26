#include "Magician_Cane_GamePlay.h"
#include "GameInstance.h"


CMagician_Cane_GamePlay::CMagician_Cane_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CMagician_Cane(pDevice, pContext)
{
}

CMagician_Cane_GamePlay::CMagician_Cane_GamePlay(const CMagician_Cane_GamePlay& rhs)
	: CMagician_Cane(rhs)
{
}

HRESULT CMagician_Cane_GamePlay::Ready_Components()
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

HRESULT CMagician_Cane_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CMagician_Cane_GamePlay* CMagician_Cane_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CMagician_Cane_GamePlay* pInstance = new CMagician_Cane_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CMagician_Cane_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CMagician_Cane_GamePlay::Clone(void* pArg)
{
	CMagician_Cane_GamePlay* pInstance = new CMagician_Cane_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CMagician_Cane_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMagician_Cane_GamePlay::Free()
{
	__super::Free();
}
