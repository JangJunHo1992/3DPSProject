#include "..\Public\Raider_GamePlay.h"

#include "GreatDualBlade_Idle.h"

CRaider_GamePlay::CRaider_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CRaider(pDevice, pContext)
{
}

CRaider_GamePlay::CRaider_GamePlay(const CRaider_GamePlay& rhs)
	: CRaider(rhs)
{
}


HRESULT CRaider_GamePlay::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CRaider_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pActor = new CActor<CRaider_GamePlay>(this);
	m_pActor->Set_State(new CGreatDualBlade_Idle());

	return S_OK;
}

void CRaider_GamePlay::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CRaider_GamePlay::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	m_pActor->Update_State(fTimeDelta);
}

void CRaider_GamePlay::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CRaider_GamePlay::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CRaider_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL_GAMEPLAY)))
		return E_FAIL;

	return S_OK;
}


CRaider_GamePlay* CRaider_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CRaider_GamePlay* pInstance = new CRaider_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CRaider_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CRaider_GamePlay* CRaider_GamePlay::Clone(void* pArg)
{
	CRaider_GamePlay* pInstance = new CRaider_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CRaider_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CRaider_GamePlay::Free()
{
	__super::Free();
	Safe_Delete(m_pActor);
}
