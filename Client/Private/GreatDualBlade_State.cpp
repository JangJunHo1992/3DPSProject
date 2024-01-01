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

#include "GreatDualBlade_Roll_Back.h"
#include "GreatDualBlade_Roll_Front.h"
#include "GreatDualBlade_Roll_Left.h"
#include "GreatDualBlade_Roll_Right.h"

#include "GreatDualBlade_Combo_01_01.h"
#include "GreatDualBlade_Combo_02_01.h"
#include "GreatDualBlade_Combo_03_01.h"
#include "GreatDualBlade_Combo_04_01.h"
#include "GreatDualBlade_Combo_05_01.h"

#include "GreatDualBlade_Hit_01.h"
#include "GreatDualBlade_Dead_01.h"
#include "GreatDualBlade_Defense_Start.h"




void CGreatDualBlade_State::Initialize(CRaider_GamePlay* pActor)
{
	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);
}

void CGreatDualBlade_State::Release(CRaider_GamePlay* pActor)
{
	Safe_Release(m_pGameInstance);
}

CState<CRaider_GamePlay>* CGreatDualBlade_State::Ground_Normal(CRaider_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	CState<CRaider_GamePlay>* pState = nullptr;


	if (m_pGameInstance->Key_Down(DIK_X))
	{
		return new CGreatDualBlade_Defense_Start();
	}

	if (m_pGameInstance->Key_Down(DIK_Z)) 
	{
		return new CGreatDualBlade_Combo_01_01();
	}

	pState = Roll(pActor, fTimeDelta, _iAnimIndex);
	if (pState)	return pState;

	pState = Run(pActor, fTimeDelta, _iAnimIndex);
	if (pState)	return pState;

	return nullptr;
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

CState<CRaider_GamePlay>* CGreatDualBlade_State::Roll(CRaider_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	if (m_pGameInstance->Key_Pressing(DIK_SPACE))
	{
		if (m_pGameInstance->Key_Pressing(DIK_DOWN))
		{
			if (CGreatDualBlade_Roll_Back::g_iAnimIndex != _iAnimIndex)
				return new CGreatDualBlade_Roll_Back();
		}
		else if (m_pGameInstance->Key_Pressing(DIK_LEFT))
		{
			if (CGreatDualBlade_Roll_Left::g_iAnimIndex != _iAnimIndex)
				return new CGreatDualBlade_Roll_Left();
		}
		else if (m_pGameInstance->Key_Pressing(DIK_RIGHT))
		{
			if (CGreatDualBlade_Roll_Right::g_iAnimIndex != _iAnimIndex)
				return new CGreatDualBlade_Roll_Right();
		}
		else 
		{
			if (CGreatDualBlade_Roll_Front::g_iAnimIndex != _iAnimIndex)
				return new CGreatDualBlade_Roll_Front();
		}
	}
	
	return nullptr;
}

CState<CRaider_GamePlay>* CGreatDualBlade_State::Hitted(CRaider_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	if (m_pGameInstance->Key_Down(DIK_C))
	{
		return new CGreatDualBlade_Hit_01();
	}
	if (m_pGameInstance->Key_Down(DIK_V))
	{
		return new CGreatDualBlade_Dead_01();
	}

	return nullptr;
}

