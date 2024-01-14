#include "JobMob2_Body_GamePlay.h"


CJobMob2_Body_GamePlay::CJobMob2_Body_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CJobMob2_Body(pDevice, pContext)
{
}

CJobMob2_Body_GamePlay::CJobMob2_Body_GamePlay(const CJobMob2_Body_GamePlay& rhs)
	: CJobMob2_Body(rhs)
{
}

HRESULT CJobMob2_Body_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_GAMEPLAY)))
		return E_FAIL;

	return S_OK;
}

HRESULT CJobMob2_Body_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CJobMob2_Body_GamePlay* CJobMob2_Body_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CJobMob2_Body_GamePlay* pInstance = new CJobMob2_Body_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CJobMob2_Body_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CJobMob2_Body_GamePlay::Clone(void* pArg)
{
	CJobMob2_Body_GamePlay* pInstance = new CJobMob2_Body_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CJobMob2_Body_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CJobMob2_Body_GamePlay::Free()
{
	__super::Free();
}
