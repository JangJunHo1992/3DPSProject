#include "JobMob1DefaultState.h"
#include "GameInstance.h"

#include "JobMob1_Idle.h"

#include "JobMob1_Walk_Front.h"

#include "JobMob1_Attack1.h"
#include "JobMob1_Attack2.h"
#include "JobMob1_Attack3.h"

// #include "Covus_Hit_01.h"
#include "JobMob1_Dead.h"


void CJobMob1DefaultState::Initialize(CJobMob1_GamePlay* pActor)
{
	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);
}

void CJobMob1DefaultState::Release(CJobMob1_GamePlay* pActor)
{
	Safe_Release(m_pGameInstance);
}

CState<CJobMob1_GamePlay>* CJobMob1DefaultState::Ground_Normal(CJobMob1_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	CState<CJobMob1_GamePlay>* pState = nullptr;


// 	if (30.f > pActor->Calc_Distance() && 10.f < pActor->Calc_Distance())
// 	{
// 		pState = Run(pActor, fTimeDelta, _iAnimIndex);
// 		if (pState)	return pState;
// 	}

	if (10.f > pActor->Calc_Distance() && 5.f < pActor->Calc_Distance())
	{
		m_pGameInstance->Play_Sound(L"ENEMY_ATTACK", L"Gardener_Vocal_01.ogg", SOUND_Monster, 1.f);
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

CState<CJobMob1_GamePlay>* CJobMob1DefaultState::Run(CJobMob1_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	_uint iRandom = rand() % 1;

	switch (iRandom)
	{
	case 0:
		pActor->Set_bLookAt(true);
		return new CJobMob1_Walk_Front();
		// 	case 1:
		// 		return new CMagician_DisappearF();
	}

}

CState<CJobMob1_GamePlay>* CJobMob1DefaultState::Attack(CJobMob1_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	_uint iRandom = rand() % 3;

	switch (iRandom)
	{
	case 0:
		pActor->Set_bLookAt(true);
		return new CJobMob1_Attack1();
	case 1:
		pActor->Set_bLookAt(true);
		return new CJobMob1_Attack2();
	case 2:
		pActor->Set_bLookAt(true);
		return new CJobMob1_Attack3();
	}

}




CState<CJobMob1_GamePlay>* CJobMob1DefaultState::Hitted(CJobMob1_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
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

