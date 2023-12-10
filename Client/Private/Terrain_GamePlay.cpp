#include "stdafx.h"
#include "Terrain_GamePlay.h"

CTerrain_GamePlay::CTerrain_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CTerrain(pDevice, pContext)
{

}

CTerrain_GamePlay::CTerrain_GamePlay(const CTerrain_GamePlay& rhs)
	: CTerrain(rhs)
{
}

HRESULT CTerrain_GamePlay::Ready_Components()
{
	return Ready_Components_Origin(LEVEL::LEVEL_GAMEPLAY);
}

HRESULT CTerrain_GamePlay::Bind_ShaderResources()
{
	if (FAILED(Bind_ShaderResources_Origin()))
		return E_FAIL;

	return S_OK;
}

CTerrain_GamePlay* CTerrain_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CTerrain_GamePlay* pInstance = new CTerrain_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CTerrain_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CTerrain_GamePlay::Clone(void* pArg)
{
	CTerrain_GamePlay* pInstance = new CTerrain_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CTerrain_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTerrain_GamePlay::Free()
{
	__super::Free();
}


