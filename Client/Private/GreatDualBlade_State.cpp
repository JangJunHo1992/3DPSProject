#include "..\Public\GreatDualBlade_State.h"
#include "GameInstance.h"

#include "GreatDualBlade_Idle.h"
#include "GreatDualBlade_Run_Front.h"
#include "GreatDualBlade_Run_Front_L45.h"
#include "GreatDualBlade_Run_Front_R45.h"
#include "GreatDualBlade_Run_Back.h"
#include "GreatDualBlade_Run_Back_L45.h"
#include "GreatDualBlade_Run_Back_R45.h"
#include "GreatDualBlade_Run_Left.h"
#include "GreatDualBlade_Run_Right.h"

void CGreatDualBlade_State::Initialize(CRaider_GamePlay* pActor)
{
	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);
}

void CGreatDualBlade_State::Release(CRaider_GamePlay* pActor)
{
	Safe_Release(m_pGameInstance);
}

CState<CRaider_GamePlay>* CGreatDualBlade_State::Run(CRaider_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	if (m_pGameInstance->Key_Pressing(DIK_UP))
	{
		if (m_pGameInstance->Key_Pressing(DIK_LEFT))
		{
			if (CGreatDualBlade_Run_Front_L45::g_iAnimIndex != _iAnimIndex)
				return new CGreatDualBlade_Run_Front_L45();
		}
		else if (m_pGameInstance->Key_Pressing(DIK_RIGHT))
		{
			if (CGreatDualBlade_Run_Front_R45::g_iAnimIndex != _iAnimIndex)
				return new CGreatDualBlade_Run_Front_R45();
		}
		else
		{
			pActor->Go_Straight(fTimeDelta);
			if (CGreatDualBlade_Run_Front::g_iAnimIndex != _iAnimIndex)
				return new CGreatDualBlade_Run_Front();
		}
	}
	else if (m_pGameInstance->Key_Pressing(DIK_DOWN))
	{
		if (m_pGameInstance->Key_Pressing(DIK_LEFT))
		{
			if (CGreatDualBlade_Run_Back_L45::g_iAnimIndex != _iAnimIndex)
				return new CGreatDualBlade_Run_Back_L45();
		}
		else if (m_pGameInstance->Key_Pressing(DIK_RIGHT))
		{
			if (CGreatDualBlade_Run_Back_R45::g_iAnimIndex != _iAnimIndex)
				return new CGreatDualBlade_Run_Back_R45();
		}
		else
		{
			pActor->Go_Backward(fTimeDelta);
			if (CGreatDualBlade_Run_Back::g_iAnimIndex != _iAnimIndex)
				return new CGreatDualBlade_Run_Back();
		}
	}
	else if (m_pGameInstance->Key_Pressing(DIK_LEFT))
	{
		if (CGreatDualBlade_Run_Left::g_iAnimIndex != _iAnimIndex)
			return new CGreatDualBlade_Run_Left();
	}
	else if (m_pGameInstance->Key_Pressing(DIK_RIGHT))
	{
		if (CGreatDualBlade_Run_Right::g_iAnimIndex != _iAnimIndex)
			return new CGreatDualBlade_Run_Right();
	}
	else
	{
		if (CGreatDualBlade_Idle::g_iAnimIndex != _iAnimIndex)
			return new CGreatDualBlade_Idle();
	}
	return nullptr;
}
