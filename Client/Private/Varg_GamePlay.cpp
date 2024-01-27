#include "Varg_GamePlay.h"
#include "GameInstance.h"
#include "Varg_Idle.h"
#include "Varg_StartIdle.h"
#include "Varg_StartDemo.h"
#include "Varg_Dead.h"
#include "Varg_Stun.h"

CVarg_GamePlay::CVarg_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CVarg(pDevice, pContext)
{
}

CVarg_GamePlay::CVarg_GamePlay(const CVarg_GamePlay& rhs)
	: CVarg(rhs)
{
}


HRESULT CVarg_GamePlay::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CVarg_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pActor = new CActor<CVarg_GamePlay>(this);
	m_pActor->Set_State(new CVarg_StartIdle);

	


	return S_OK;
}

void CVarg_GamePlay::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
	if (nullptr == m_pTargetPlayer)
		Search_Target();
	if (m_bLookAt == true)
	{
		Look_At_Target();
		m_bLookAt = false;
	}
	if (m_pGameInstance->Get_DIKeyState(DIK_1))
	{
		Set_CutSceneDead(true);
	}
	if (40.f < Calc_Distance() && m_bCheckStart)
	{
		m_pActor->Set_State(new CVarg_StartDemo());
		m_bCheckStart = false;
		m_bStartScene = true;

	}
}

void CVarg_GamePlay::Tick(_float fTimeDelta)
{
	if (VargStatus.m_iHP < 0 && Get_CutSceneDead()==true)
		Set_Dead();
	else if (VargStatus.m_iHP < 0)
		m_pActor->Set_State(new CVarg_Stun());

	__super::Tick(fTimeDelta);
	m_pActor->Update_State(fTimeDelta);
}

void CVarg_GamePlay::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CVarg_GamePlay::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CVarg_GamePlay::Ready_Components()
{
	m_pGameInstance->Get_NextLevel();
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
void CVarg_GamePlay::Set_Dead()
{
	m_bCheckDead = true;
	m_pActor->Set_State(new CVarg_Dead());
}

CVarg_GamePlay* CVarg_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CVarg_GamePlay* pInstance = new CVarg_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CVarg_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CVarg_GamePlay* CVarg_GamePlay::Clone(void* pArg)
{
	CVarg_GamePlay* pInstance = new CVarg_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CVarg_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CVarg_GamePlay::Free()
{
	__super::Free();
	Safe_Delete(m_pActor);
}
