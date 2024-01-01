#include "..\Public\Golem_Body_GamePlay.h"


CGolem_Body_GamePlay::CGolem_Body_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGolem_Body(pDevice, pContext)
{
}

CGolem_Body_GamePlay::CGolem_Body_GamePlay(const CGolem_Body_GamePlay& rhs)
	: CGolem_Body(rhs)
{
}

HRESULT CGolem_Body_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_GAMEPLAY)))
		return E_FAIL;

	return S_OK;
}

HRESULT CGolem_Body_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

CGolem_Body_GamePlay* CGolem_Body_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CGolem_Body_GamePlay* pInstance = new CGolem_Body_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CGolem_Body_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CGolem_Body_GamePlay::Clone(void* pArg)
{
	CGolem_Body_GamePlay* pInstance = new CGolem_Body_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CGolem_Body_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CGolem_Body_GamePlay::Free()
{
	__super::Free();
}
