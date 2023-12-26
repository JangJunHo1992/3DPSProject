#include "..\Public\Massive_Greate_Sword_State.h"
#include "GameInstance.h"

#include "Massive_Greate_Sword_Idle01.h"

#include "Massive_Greate_Sword_Move_Run_Front.h"
#include "Massive_Greate_Sword_Move_Run_Front_L45.h"
#include "Massive_Greate_Sword_Move_Run_Front_R45.h"
#include "Massive_Greate_Sword_Move_Run_Back.h"
#include "Massive_Greate_Sword_Move_Run_Back_L45.h"
#include "Massive_Greate_Sword_Move_Run_Back_R45.h"
#include "Massive_Greate_Sword_Move_Run_Left.h"
#include "Massive_Greate_Sword_Move_Run_Right.h"

#include "Massive_Greate_Sword_Roll_Back.h"
#include "Massive_Greate_Sword_Roll_Front.h"
#include "Massive_Greate_Sword_Roll_Left.h"
#include "Massive_Greate_Sword_Roll_Right.h"

#include "Massive_Greate_Sword_Combo01_1.h"
#include "Massive_Greate_Sword_Combo01_2.h"
#include "Massive_Greate_Sword_Combo01_3.h"

#include "Massive_Greate_Sword_Hit_Front.h"
#include "Massive_Greate_Sword_Dead01.h"
#include "Massive_Greate_Sword_Defense01_Start.h"




void CMassive_Greate_Sword_State::Initialize(CDarkKnight_GamePlay* pActor)
{
	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);
}

void CMassive_Greate_Sword_State::Release(CDarkKnight_GamePlay* pActor)
{
	Safe_Release(m_pGameInstance);
}

CState<CDarkKnight_GamePlay>* CMassive_Greate_Sword_State::Ground_Normal(CDarkKnight_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	CState<CDarkKnight_GamePlay>* pState = nullptr;


	if (m_pGameInstance->Key_Down(DIK_X))
	{
		return new CMassive_Greate_Sword_Defense01_Start();
	}

	if (m_pGameInstance->Key_Down(DIK_Z))
	{
		return new CMassive_Greate_Sword_Combo01_1();
	}

	pState = Roll(pActor, fTimeDelta, _iAnimIndex);
	if (pState)	return pState;

	pState = Run(pActor, fTimeDelta, _iAnimIndex);
	if (pState)	return pState;

	return nullptr;
}

CState<CDarkKnight_GamePlay>* CMassive_Greate_Sword_State::Run(CDarkKnight_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	if (m_pGameInstance->Key_Pressing(DIK_UP))
	{
		if (m_pGameInstance->Key_Pressing(DIK_LEFT))
		{
			if (CMassive_Greate_Sword_Move_Run_Front_L45::g_iAnimIndex != _iAnimIndex)
				return new CMassive_Greate_Sword_Move_Run_Front_L45();
		}
		else if (m_pGameInstance->Key_Pressing(DIK_RIGHT))
		{
			if (CMassive_Greate_Sword_Move_Run_Front_R45::g_iAnimIndex != _iAnimIndex)
				return new CMassive_Greate_Sword_Move_Run_Front_R45();
		}
		else
		{
			if (CMassive_Greate_Sword_Move_Run_Front::g_iAnimIndex != _iAnimIndex)
				return new CMassive_Greate_Sword_Move_Run_Front();
		}
	}
	else if (m_pGameInstance->Key_Pressing(DIK_DOWN))
	{
		if (m_pGameInstance->Key_Pressing(DIK_LEFT))
		{
			if (CMassive_Greate_Sword_Move_Run_Back_L45::g_iAnimIndex != _iAnimIndex)
				return new CMassive_Greate_Sword_Move_Run_Back_L45();
		}
		else if (m_pGameInstance->Key_Pressing(DIK_RIGHT))
		{
			if (CMassive_Greate_Sword_Move_Run_Back_R45::g_iAnimIndex != _iAnimIndex)
				return new CMassive_Greate_Sword_Move_Run_Back_R45();
		}
		else
		{
			if (CMassive_Greate_Sword_Move_Run_Back::g_iAnimIndex != _iAnimIndex)
				return new CMassive_Greate_Sword_Move_Run_Back();
		}
	}
	else if (m_pGameInstance->Key_Pressing(DIK_LEFT))
	{
		if (CMassive_Greate_Sword_Move_Run_Left::g_iAnimIndex != _iAnimIndex)
			return new CMassive_Greate_Sword_Move_Run_Left();
	}
	else if (m_pGameInstance->Key_Pressing(DIK_RIGHT))
	{
		if (CMassive_Greate_Sword_Move_Run_Right::g_iAnimIndex != _iAnimIndex)
			return new CMassive_Greate_Sword_Move_Run_Right();
	}
	else
	{
		if (CMassive_Greate_Sword_Idle01::g_iAnimIndex != _iAnimIndex)
			return new CMassive_Greate_Sword_Idle01();
	}
	return nullptr;
}

CState<CDarkKnight_GamePlay>* CMassive_Greate_Sword_State::Roll(CDarkKnight_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	if (m_pGameInstance->Key_Pressing(DIK_SPACE))
	{
		if (m_pGameInstance->Key_Pressing(DIK_DOWN))
		{
			if (CMassive_Greate_Sword_Roll_Back::g_iAnimIndex != _iAnimIndex)
				return new CMassive_Greate_Sword_Roll_Back();
		}
		else if (m_pGameInstance->Key_Pressing(DIK_LEFT))
		{
			if (CMassive_Greate_Sword_Roll_Left::g_iAnimIndex != _iAnimIndex)
				return new CMassive_Greate_Sword_Roll_Left();
		}
		else if (m_pGameInstance->Key_Pressing(DIK_RIGHT))
		{
			if (CMassive_Greate_Sword_Roll_Right::g_iAnimIndex != _iAnimIndex)
				return new CMassive_Greate_Sword_Roll_Right();
		}
		else
		{
			if (CMassive_Greate_Sword_Roll_Front::g_iAnimIndex != _iAnimIndex)
				return new CMassive_Greate_Sword_Roll_Front();
		}
	}

	return nullptr;
}

CState<CDarkKnight_GamePlay>* CMassive_Greate_Sword_State::Hitted(CDarkKnight_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	if (m_pGameInstance->Key_Down(DIK_C))
	{
		return new CMassive_Greate_Sword_Hit_Front();
	}
	if (m_pGameInstance->Key_Down(DIK_V))
	{
		return new CMassive_Greate_Sword_Dead01();
	}

	return nullptr;
}

