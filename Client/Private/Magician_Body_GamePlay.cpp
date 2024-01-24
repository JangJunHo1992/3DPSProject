#include "Magician_Body_GamePlay.h"
#include "GameInstance.h"

CMagician_Body_GamePlay::CMagician_Body_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CMagician_Body(pDevice, pContext)
{
}

CMagician_Body_GamePlay::CMagician_Body_GamePlay(const CMagician_Body_GamePlay& rhs)
	: CMagician_Body(rhs)
{
}

HRESULT CMagician_Body_GamePlay::Ready_Components()
{
// 	m_pGameInstance->Get_NextLevel();
// 	switch (m_pGameInstance->Get_NextLevel())
// 	{
// 	case 2:
// 		if (FAILED(Ready_Components_Origin(LEVEL_GAMEPLAY)))
// 			return E_FAIL;
// 		break;
// 	case 6:
// 		if (FAILED(Ready_Components_Origin(LEVEL_BOSS1)))
// 			return E_FAIL;
// 		break;
// 	case 7:
// 		if (FAILED(Ready_Components_Origin(LEVEL_BOSS2)))
// 			return E_FAIL;
// 		break;
// 	default:
// 		break;
// 	}
	if (FAILED(Ready_Components_Origin(LEVEL_BOSS2)))
		return E_FAIL;
	return S_OK;
}

HRESULT CMagician_Body_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CMagician_Body_GamePlay* CMagician_Body_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CMagician_Body_GamePlay* pInstance = new CMagician_Body_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CMagician_Body_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CMagician_Body_GamePlay::Clone(void* pArg)
{
	CMagician_Body_GamePlay* pInstance = new CMagician_Body_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CMagician_Body_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMagician_Body_GamePlay::Free()
{
	__super::Free();
}
