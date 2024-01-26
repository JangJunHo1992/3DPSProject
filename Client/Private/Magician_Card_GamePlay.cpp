#include "Magician_Card_GamePlay.h"
#include "GameInstance.h"


CMagician_Card_GamePlay::CMagician_Card_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CMagician_Card(pDevice, pContext)
{
}

CMagician_Card_GamePlay::CMagician_Card_GamePlay(const CMagician_Card_GamePlay& rhs)
	: CMagician_Card(rhs)
{
}

HRESULT CMagician_Card_GamePlay::Ready_Components()
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

HRESULT CMagician_Card_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CMagician_Card_GamePlay* CMagician_Card_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CMagician_Card_GamePlay* pInstance = new CMagician_Card_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CMagician_Card_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CMagician_Card_GamePlay::Clone(void* pArg)
{
	CMagician_Card_GamePlay* pInstance = new CMagician_Card_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CMagician_Card_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMagician_Card_GamePlay::Free()
{
	__super::Free();
}
