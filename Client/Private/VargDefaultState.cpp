#include "VargDefaultState.h"
#include "GameInstance.h"

#include "Varg_Idle.h"
// #include "Varg_Run_Front.h"
// #include "Varg_Run_Front_L45.h"
// #include "Varg_Run_Front_R45.h"
// #include "Varg_Run_Back.h"
// #include "Varg_Run_Back_L45.h"
// #include "Varg_Run_Back_R45.h"
// #include "Varg_Run_Left.h"
// #include "Varg_Run_Right.h"
// 
#include "Varg_Walk_Front.h"
#include "Varg_Walk_Back.h"
#include "Varg_Walk_Left.h"
#include "Varg_Walk_Right.h"
// 
#include "Varg_RaidAttack1.h"
#include "Varg_RaidAttack2.h"
// 
#include "Varg_Attack1_1.h"
#include "Varg_Attack2_1.h"
#include "Varg_Attack3.h"

// #include "Covus_Hit_01.h"
// #include "Covus_Dead_01.h"
// #include "Covus_Defense_Start.h"


void CVargDefaultState::Initialize(CVarg_GamePlay* pActor)
{
	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);
}

void CVargDefaultState::Release(CVarg_GamePlay* pActor)
{
	Safe_Release(m_pGameInstance);
}

CState<CVarg_GamePlay>* CVargDefaultState::Ground_Normal(CVarg_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	CState<CVarg_GamePlay>* pState = nullptr;


	if (30.f > pActor->Calc_Distance() && 18.f < pActor->Calc_Distance())
	{
		pState = Run(pActor, fTimeDelta, _iAnimIndex);
		if (pState)	return pState;
	}

	if (18.f > pActor->Calc_Distance() && 7.f < pActor->Calc_Distance())
	{

		pState = RaidAttack(pActor, fTimeDelta, _iAnimIndex);
		if (pState)	return pState;
	}

	if (7.f > pActor->Calc_Distance() && 0.5f < pActor->Calc_Distance())
	{

		pState = Attack(pActor, fTimeDelta, _iAnimIndex);
		if (pState)	return pState;
	}

	return nullptr;
}

CState<CVarg_GamePlay>* CVargDefaultState::Run(CVarg_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	_uint iRandom = rand() % 1;

	switch (iRandom)
	{
	case 0:
		pActor->Set_bLookAt(true);
		return new CVarg_Walk_Front();
		// 	case 1:
		// 		return new CMagician_DisappearF();
	}

}

CState<CVarg_GamePlay>* CVargDefaultState::Attack(CVarg_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	_uint iRandom = rand() % 3;

	switch (iRandom)
	{
	case 0:
		pActor->Set_bLookAt(true);
		return new CVarg_Attack1_1();
	case 1:
		pActor->Set_bLookAt(true);
		return new CVarg_Attack2_1();
	case 2:
		pActor->Set_bLookAt(true);
		return new CVarg_Attack3();
	}

}

CState<CVarg_GamePlay>* CVargDefaultState::RaidAttack(CVarg_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	_uint iRandom = rand() % 2;

	switch (iRandom)
	{
	case 0:
		pActor->Set_bLookAt(true);
		return new CVarg_RaidAttack1();
	case 1:			
		pActor->Set_bLookAt(true);
		return new CVarg_RaidAttack2();
	}
}


CState<CVarg_GamePlay>* CVargDefaultState::Hitted(CVarg_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
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

