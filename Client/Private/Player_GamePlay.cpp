#include "stdafx.h"
#include "..\Public\Player_GamePlay.h"

#include "GameInstance.h"


CPlayer_GamePlay::CPlayer_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CPlayer(pDevice, pContext)
{

}

CPlayer_GamePlay::CPlayer_GamePlay(const CPlayer_GamePlay& rhs)
	: CPlayer(rhs)
{
}

HRESULT CPlayer_GamePlay::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPlayer_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

void CPlayer_GamePlay::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CPlayer_GamePlay::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CPlayer_GamePlay::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CPlayer_GamePlay::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPlayer_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL_GAMEPLAY)))
		return E_FAIL;

	return S_OK;
}


CPlayer_GamePlay* CPlayer_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CPlayer_GamePlay* pInstance = new CPlayer_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CPlayer_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CPlayer_GamePlay::Clone(void* pArg)
{
	CPlayer_GamePlay* pInstance = new CPlayer_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CPlayer_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CPlayer_GamePlay::Free()
{
	__super::Free();
}

