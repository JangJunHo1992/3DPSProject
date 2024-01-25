#include "DefaultState.h"
#include "GameInstance.h"

#include "Player_Idle.h"
#include "Player_Run_Front.h"
#include "Player_Run_Front_L45.h"
#include "Player_Run_Front_R45.h"
#include "Player_Run_Back.h"
#include "Player_Run_Back_L45.h"
#include "Player_Run_Back_R45.h"
#include "Player_Run_Left.h"
#include "Player_Run_Right.h"
		 
#include "Player_Walk_Front.h"
#include "Player_Walk_Front_L45.h"
#include "Player_Walk_Front_R45.h"
#include "Player_Walk_Back.h"
#include "Player_Walk_Back_L45.h"
#include "Player_Walk_Back_R45.h"
#include "Player_Walk_Left.h"
#include "Player_Walk_Right.h"
		 
#include "Player_Dash_Back.h"
#include "Player_Dash_Front.h"
#include "Player_Dash_Left.h"
#include "Player_Dash_Right.h"

#include "Covus_Attack1.h"

#include "Covus_HurtMFL.h"
#include "Covus_HurtMFR.h"
#include "Covus_HurtSL.h"
#include "Covus_HurtSR.h"

#include "Covus_Dead.h"
#include "Covus_Parry_L.h"


void CDefaultState::Initialize(CCovus_GamePlay* pActor)
{
	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);
}

void CDefaultState::Release(CCovus_GamePlay* pActor)
{
	Safe_Release(m_pGameInstance);
}

CState<CCovus_GamePlay>* CDefaultState::Ground_Normal(CCovus_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	CState<CCovus_GamePlay>* pState = nullptr;


	if (m_pGameInstance->Key_Down(DIK_F))
	{
		return new CCovus_Parry_L();
	}


	if (m_pGameInstance->Mouse_Down(DIM_LB))
	{
		return new CCovus_Attack1;
	}
	
	pState = Run(pActor, fTimeDelta, _iAnimIndex);
	if (pState)	return pState;

	pState = Dash(pActor, fTimeDelta, _iAnimIndex);
	if (pState)	return pState;

	pState = Hitted(pActor, fTimeDelta, _iAnimIndex);
	if (pState)	return pState;

	return nullptr;
}

CState<CCovus_GamePlay>* CDefaultState::Run(CCovus_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	if (m_pGameInstance->Key_Pressing(DIK_LSHIFT))
	{
		if (m_pGameInstance->Key_Pressing(DIK_W))
		{
			if (m_pGameInstance->Key_Pressing(DIK_A))
			{
				pActor->Set_CheckRotatePlayer(true);
				if (CCovus_Run_Front_L45::g_iAnimIndex != _iAnimIndex)
					return new CCovus_Run_Front_L45();
			}
			else if (m_pGameInstance->Key_Pressing(DIK_D))
			{
				pActor->Set_CheckRotatePlayer(true);
				if (CCovus_Run_Front_R45::g_iAnimIndex != _iAnimIndex)
					return new CCovus_Run_Front_R45();
			}
			else
			{
				pActor->Set_CheckRotatePlayer(true);

				if (CCovus_Run_Front::g_iAnimIndex != _iAnimIndex)
					return new CCovus_Run_Front();
				
			}
		}
		else if (m_pGameInstance->Key_Pressing(DIK_S))
		{
			if (m_pGameInstance->Key_Pressing(DIK_A))
			{
				pActor->Set_CheckRotatePlayer(true);
				if (CCovus_Run_Back_L45::g_iAnimIndex != _iAnimIndex)
					return new CCovus_Run_Back_L45();
			}
			else if (m_pGameInstance->Key_Pressing(DIK_D))
			{
				pActor->Set_CheckRotatePlayer(true);
				if (CCovus_Run_Back_R45::g_iAnimIndex != _iAnimIndex)
					return new CCovus_Run_Back_R45();
			}
			else
			{
				pActor->Set_CheckRotatePlayer(true);
				if (CCovus_Run_Back::g_iAnimIndex != _iAnimIndex)
					return new CCovus_Run_Back();
			}
		}
		else if (m_pGameInstance->Key_Pressing(DIK_A))
		{
			pActor->Set_CheckRotatePlayer(true);
			if (CCovus_Run_Left::g_iAnimIndex != _iAnimIndex)
				return new CCovus_Run_Left();
		}
		else if (m_pGameInstance->Key_Pressing(DIK_D))
		{
			pActor->Set_CheckRotatePlayer(true);
			if (CCovus_Run_Right::g_iAnimIndex != _iAnimIndex)
				return new CCovus_Run_Right();
		}
		else
		{
			if (CCovus_Idle::g_iAnimIndex != _iAnimIndex)
				return new CCovus_Idle();
		}
	}
	else
	{
		if (m_pGameInstance->Key_Pressing(DIK_W))
		{
			if (m_pGameInstance->Key_Pressing(DIK_A))
			{
				pActor->Set_CheckRotatePlayer(true);
				if (CCovus_Walk_Front_L45::g_iAnimIndex != _iAnimIndex)
					return new CCovus_Walk_Front_L45();
			}
			else if (m_pGameInstance->Key_Pressing(DIK_D))
			{
				pActor->Set_CheckRotatePlayer(true);
				if (CCovus_Walk_Front_R45::g_iAnimIndex != _iAnimIndex)
					return new CCovus_Walk_Front_R45();
			}
			else
			{
				pActor->Set_CheckRotatePlayer(true);
				if (CCovus_Walk_Front::g_iAnimIndex != _iAnimIndex)
					return new CCovus_Walk_Front();
			}
		}
		else if (m_pGameInstance->Key_Pressing(DIK_S))
		{
			if (m_pGameInstance->Key_Pressing(DIK_A))
			{
				pActor->Set_CheckRotatePlayer(true);
				if (CCovus_Walk_Back_L45::g_iAnimIndex != _iAnimIndex)
					return new CCovus_Walk_Back_L45();
			}
			else if (m_pGameInstance->Key_Pressing(DIK_D))
			{
				pActor->Set_CheckRotatePlayer(true);
				if (CCovus_Walk_Back_R45::g_iAnimIndex != _iAnimIndex)
					return new CCovus_Walk_Back_R45();
			}
			else
			{
				pActor->Set_CheckRotatePlayer(true);
				if (CCovus_Walk_Back::g_iAnimIndex != _iAnimIndex)
					return new CCovus_Walk_Back();
			}
		}
		else if (m_pGameInstance->Key_Pressing(DIK_A))
		{
			pActor->Set_CheckRotatePlayer(true);
			if (CCovus_Walk_Left::g_iAnimIndex != _iAnimIndex)
				return new CCovus_Walk_Left();
		}
		else if (m_pGameInstance->Key_Pressing(DIK_D))
		{
			pActor->Set_CheckRotatePlayer(true);
			if (CCovus_Walk_Right::g_iAnimIndex != _iAnimIndex)
				return new CCovus_Walk_Right();
		}
		else
		{
			if (CCovus_Idle::g_iAnimIndex != _iAnimIndex)
				return new CCovus_Idle();
		}
	}
	
	return nullptr;
}

CState<CCovus_GamePlay>* CDefaultState::Dash(CCovus_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	if (m_pGameInstance->Key_Pressing(DIK_SPACE))
	{
		if (m_pGameInstance->Key_Pressing(DIK_S))
		{
			pActor->Set_CheckRotatePlayer(true);
			if (CCovus_Dash_Back::g_iAnimIndex != _iAnimIndex)
				return new CCovus_Dash_Back();
		}
		else if (m_pGameInstance->Key_Pressing(DIK_A))
		{
			pActor->Set_CheckRotatePlayer(true);
			if (CCovus_Dash_Left::g_iAnimIndex != _iAnimIndex)
				return new CCovus_Dash_Left();
		}
		else if (m_pGameInstance->Key_Pressing(DIK_D))
		{
			pActor->Set_CheckRotatePlayer(true);
			if (CCovus_Dash_Right::g_iAnimIndex != _iAnimIndex)
				return new CCovus_Dash_Right();
		}
		else if (m_pGameInstance->Key_Pressing(DIK_W))
		{
			pActor->Set_CheckRotatePlayer(true);
			if (CCovus_Dash_Front::g_iAnimIndex != _iAnimIndex)
				return new CCovus_Dash_Front();
		}
		else
		{
			if (CCovus_Idle::g_iAnimIndex != _iAnimIndex)
				return new CCovus_Idle();
		}
	}

	return nullptr;
}


CState<CCovus_GamePlay>* CDefaultState::Hitted(CCovus_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
// 	if (m_pGameInstance->Key_Down(DIK_C))
// 	{
// 		return new CGreatDualBlade_Hit_01();
// 	}
// 	if (m_pGameInstance->Key_Down(DIK_V))
// 	{
// 		return new CGreatDualBlade_Dead_01();
// 	}

	return nullptr;
}

