#include "JobMob2DefaultState.h"
#include "GameInstance.h"

#include "JobMob2_Idle.h"

#include "JobMob2_Walk_Front.h"

#include "JobMob2_Attack1.h"
#include "JobMob2_Attack2.h"
#include "JobMob2_Attack3.h"
#include "JobMob2_Attack4.h"
#include "JobMob2_Attack5.h"

// #include "Covus_Hit_01.h"
#include "JobMob2_Dead.h"


void CJobMob2DefaultState::Initialize(CJobMob2_GamePlay* pActor)
{
	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);
}

void CJobMob2DefaultState::Release(CJobMob2_GamePlay* pActor)
{
	Safe_Release(m_pGameInstance);
}

CState<CJobMob2_GamePlay>* CJobMob2DefaultState::Ground_Normal(CJobMob2_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	CState<CJobMob2_GamePlay>* pState = nullptr;


// 	if (30.f > pActor->Calc_Distance() && 18.f < pActor->Calc_Distance())
// 	{
// 		pState = Run(pActor, fTimeDelta, _iAnimIndex);
// 		if (pState)	return pState;
// 	}

	if (10.f > pActor->Calc_Distance() && 5.f < pActor->Calc_Distance())
	{

		pState = Run(pActor, fTimeDelta, _iAnimIndex);
		if (pState)	return pState;
	}

	if (5.f > pActor->Calc_Distance() && 0.1f < pActor->Calc_Distance())
	{

		pState = Attack(pActor, fTimeDelta, _iAnimIndex);
		if (pState)	return pState;
	}

	return nullptr;
}

CState<CJobMob2_GamePlay>* CJobMob2DefaultState::Run(CJobMob2_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	_uint iRandom = rand() % 1;

	switch (iRandom)
	{
	case 0:
		pActor->Set_bLookAt(true);
		return new CJobMob2_Walk_Front();
		// 	case 1:
		// 		return new CMagician_DisappearF();
	}

}

CState<CJobMob2_GamePlay>* CJobMob2DefaultState::Attack(CJobMob2_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	_uint iRandom = rand() % 5;

	switch (iRandom)
	{
	case 0:
		pActor->Set_bLookAt(true);
		return new CJobMob2_Attack1();
	case 1:
		pActor->Set_bLookAt(true);
		return new CJobMob2_Attack2();
	case 2:
		pActor->Set_bLookAt(true);
		return new CJobMob2_Attack3();
	case 3:
		pActor->Set_bLookAt(true);
		return new CJobMob2_Attack4();
	case 4:
		pActor->Set_bLookAt(true);
		return new CJobMob2_Attack5();
	}

}

CState<CJobMob2_GamePlay>* CJobMob2DefaultState::RaidAttack(CJobMob2_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	
}


CState<CJobMob2_GamePlay>* CJobMob2DefaultState::Hitted(CJobMob2_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
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

