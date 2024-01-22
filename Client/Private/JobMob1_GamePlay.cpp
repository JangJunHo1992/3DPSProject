#include "JobMob1_GamePlay.h"
#include "GameInstance.h"
#include "JobMob1_Idle.h"
#include "JobMob1_Dead.h"



CJobMob1_GamePlay::CJobMob1_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CJobMob1(pDevice, pContext)
{
}

CJobMob1_GamePlay::CJobMob1_GamePlay(const CJobMob1_GamePlay& rhs)
	: CJobMob1(rhs)
{
}


HRESULT CJobMob1_GamePlay::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CJobMob1_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pActor = new CActor<CJobMob1_GamePlay>(this);
	m_pActor->Set_State(new CJobMob1_Idle);

	Search_Target();


	return S_OK;
}

void CJobMob1_GamePlay::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
	if (nullptr == m_pTargetPlayer)
		Search_Target();
	if (m_bLookAt == true)
	{
		Look_At_Target();
		m_bLookAt = false;
	}
}

void CJobMob1_GamePlay::Tick(_float fTimeDelta)
{
	if (JobMob1Status.m_iHP < 0)
	{
		Set_Dead();
	}
	__super::Tick(fTimeDelta);
	m_pActor->Update_State(fTimeDelta);
}

void CJobMob1_GamePlay::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CJobMob1_GamePlay::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CJobMob1_GamePlay::Set_Dead()
{
	m_pActor->Set_State(new CJobMob1_Dead());
}

HRESULT CJobMob1_GamePlay::Ready_Components()
{
	//m_pGameInstance->Get_NextLevel();
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


CJobMob1_GamePlay* CJobMob1_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CJobMob1_GamePlay* pInstance = new CJobMob1_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CJobMob1_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CJobMob1_GamePlay* CJobMob1_GamePlay::Clone(void* pArg)
{
	CJobMob1_GamePlay* pInstance = new CJobMob1_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CJobMob1_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CJobMob1_GamePlay::Free()
{
	__super::Free();
	Safe_Delete(m_pActor);
}
