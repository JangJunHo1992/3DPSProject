#include "MagicianDefaultState.h"
#include "GameInstance.h"

// #include "Magician_Idle.h"
// #include "Magician_Run_Front.h"
// #include "Magician_Run_Front_L45.h"
// #include "Magician_Run_Front_R45.h"
// #include "Magician_Run_Back.h"
// #include "Magician_Run_Back_L45.h"
// #include "Magician_Run_Back_R45.h"
// #include "Magician_Run_Left.h"
// #include "Magician_Run_Right.h"
// 
// #include "Magician_Walk_Front.h"
// #include "Magician_Walk_Front_L45.h"
// #include "Magician_Walk_Front_R45.h"
// #include "Magician_Walk_Back.h"
// #include "Magician_Walk_Back_L45.h"
// #include "Magician_Walk_Back_R45.h"
// #include "Magician_Walk_Left.h"
// #include "Magician_Walk_Right.h"
// 
// #include "Magician_Dash_Back.h"
// #include "Magician_Dash_Front.h"
// #include "Magician_Dash_Left.h"
// #include "Magician_Dash_Right.h"
// 
// #include "Magician_Attack1.h"

// #include "Covus_Hit_01.h"
// #include "Covus_Dead_01.h"
// #include "Covus_Defense_Start.h"


void CMagicianDefaultState::Initialize(CMagician_GamePlay* pActor)
{
	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);
}

void CMagicianDefaultState::Release(CMagician_GamePlay* pActor)
{
	Safe_Release(m_pGameInstance);
}

CState<CMagician_GamePlay>* CMagicianDefaultState::Ground_Normal(CMagician_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	CState<CMagician_GamePlay>* pState = nullptr;


	// 	if (m_pGameInstance->Key_Down(DIK_X))
	// 	{
	// 		return new CGreatDualBlade_Defense_Start();
	// 	}

// 
// 	if (m_pGameInstance->Mouse_Down(DIM_LB))
// 	{
// 		return new CCovus_Attack1;
// 	}

	pState = Run(pActor, fTimeDelta, _iAnimIndex);
	if (pState)	return pState;


	pState = Dash(pActor, fTimeDelta, _iAnimIndex);
	if (pState)	return pState;

	return nullptr;
}

CState<CMagician_GamePlay>* CMagicianDefaultState::Run(CMagician_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
// 	if (m_pGameInstance->Key_Pressing(DIK_LSHIFT))
// 	{
// 		if (m_pGameInstance->Key_Pressing(DIK_W))
// 		{
// 			if (m_pGameInstance->Key_Pressing(DIK_A))
// 			{
// 				if (CCovus_Run_Front_L45::g_iAnimIndex != _iAnimIndex)
// 					return new CCovus_Run_Front_L45();
// 			}
// 			else if (m_pGameInstance->Key_Pressing(DIK_D))
// 			{
// 				if (CCovus_Run_Front_R45::g_iAnimIndex != _iAnimIndex)
// 					return new CCovus_Run_Front_R45();
// 			}
// 			else
// 			{
// 				if (CCovus_Run_Front::g_iAnimIndex != _iAnimIndex)
// 					return new CCovus_Run_Front();
// 			}
// 		}
// 		else if (m_pGameInstance->Key_Pressing(DIK_S))
// 		{
// 			if (m_pGameInstance->Key_Pressing(DIK_A))
// 			{
// 				if (CCovus_Run_Back_L45::g_iAnimIndex != _iAnimIndex)
// 					return new CCovus_Run_Back_L45();
// 			}
// 			else if (m_pGameInstance->Key_Pressing(DIK_D))
// 			{
// 				if (CCovus_Run_Back_R45::g_iAnimIndex != _iAnimIndex)
// 					return new CCovus_Run_Back_R45();
// 			}
// 			else
// 			{
// 				if (CCovus_Run_Back::g_iAnimIndex != _iAnimIndex)
// 					return new CCovus_Run_Back();
// 			}
// 		}
// 		else if (m_pGameInstance->Key_Pressing(DIK_A))
// 		{
// 			if (CCovus_Run_Left::g_iAnimIndex != _iAnimIndex)
// 				return new CCovus_Run_Left();
// 		}
// 		else if (m_pGameInstance->Key_Pressing(DIK_D))
// 		{
// 			if (CCovus_Run_Right::g_iAnimIndex != _iAnimIndex)
// 				return new CCovus_Run_Right();
// 		}
// 		else
// 		{
// 			if (CCovus_Idle::g_iAnimIndex != _iAnimIndex)
// 				return new CCovus_Idle();
// 		}
// 	}
	
// 		if (m_pGameInstance->Key_Pressing(DIK_W))
// 		{
// 			if (m_pGameInstance->Key_Pressing(DIK_A))
// 			{
// 				if (CCovus_Walk_Front_L45::g_iAnimIndex != _iAnimIndex)
// 					return new CCovus_Walk_Front_L45();
// 			}
// 			else if (m_pGameInstance->Key_Pressing(DIK_D))
// 			{
// 				if (CCovus_Walk_Front_R45::g_iAnimIndex != _iAnimIndex)
// 					return new CCovus_Walk_Front_R45();
// 			}
// 			else
// 			{
// 				if (CCovus_Walk_Front::g_iAnimIndex != _iAnimIndex)
// 					return new CCovus_Walk_Front();
// 			}
// 		}
// 		else if (m_pGameInstance->Key_Pressing(DIK_S))
// 		{
// 			if (m_pGameInstance->Key_Pressing(DIK_A))
// 			{
// 				if (CCovus_Walk_Back_L45::g_iAnimIndex != _iAnimIndex)
// 					return new CCovus_Walk_Back_L45();
// 			}
// 			else if (m_pGameInstance->Key_Pressing(DIK_D))
// 			{
// 				if (CCovus_Walk_Back_R45::g_iAnimIndex != _iAnimIndex)
// 					return new CCovus_Walk_Back_R45();
// 			}
// 			else
// 			{
// 				if (CCovus_Walk_Back::g_iAnimIndex != _iAnimIndex)
// 					return new CCovus_Walk_Back();
// 			}
// 		}
// 		else if (m_pGameInstance->Key_Pressing(DIK_A))
// 		{
// 			if (CCovus_Walk_Left::g_iAnimIndex != _iAnimIndex)
// 				return new CCovus_Walk_Left();
// 		}
// 		else if (m_pGameInstance->Key_Pressing(DIK_D))
// 		{
// 			if (CCovus_Walk_Right::g_iAnimIndex != _iAnimIndex)
// 				return new CCovus_Walk_Right();
// 		}
// 		else
// 		{
// 			if (CCovus_Idle::g_iAnimIndex != _iAnimIndex)
// 				return new CCovus_Idle();
// 		}


	return nullptr;
}

CState<CMagician_GamePlay>* CMagicianDefaultState::Dash(CMagician_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
// 	if (m_pGameInstance->Key_Pressing(DIK_SPACE))
// 	{
// 		if (m_pGameInstance->Key_Pressing(DIK_S))
// 		{
// 			if (CCovus_Dash_Back::g_iAnimIndex != _iAnimIndex)
// 				return new CCovus_Dash_Back();
// 		}
// 		else if (m_pGameInstance->Key_Pressing(DIK_A))
// 		{
// 			if (CCovus_Dash_Left::g_iAnimIndex != _iAnimIndex)
// 				return new CCovus_Dash_Left();
// 		}
// 		else if (m_pGameInstance->Key_Pressing(DIK_D))
// 		{
// 			if (CCovus_Dash_Right::g_iAnimIndex != _iAnimIndex)
// 				return new CCovus_Dash_Right();
// 		}
// 		else if (m_pGameInstance->Key_Pressing(DIK_W))
// 		{
// 			if (CCovus_Dash_Front::g_iAnimIndex != _iAnimIndex)
// 				return new CCovus_Dash_Front();
// 		}
// 	}

	return nullptr;
}


CState<CMagician_GamePlay>* CMagicianDefaultState::Hitted(CMagician_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
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

