#include "MagicianDefaultState.h"
#include "GameInstance.h"

#include "Magician_Idle.h"

#include "Magician_Walk_Front.h"
#include "Magician_Walk_Back.h"
#include "Magician_Walk_Left.h"
#include "Magician_Walk_Right.h"
 
#include "Magician_DisappearB.h"
#include "Magician_DisappearF.h"
#include "Magician_DisappearL.h"
#include "Magician_DisappearR.h"

#include "Magician_Attack1.h"
#include "Magician_Attack4.h"
#include "Magician_Attack5.h"

#include "Magician_Shoot1.h"
#include "Magician_Shoot2.h"
#include "Magician_Shoot3.h"
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

	


	if (30.f > pActor->Calc_Distance()&& 15.f <pActor->Calc_Distance())
	{
		pState = WalkandDisappear(pActor, fTimeDelta, _iAnimIndex);
		if (pState)	return pState;
	}
		

	if (15.f > pActor->Calc_Distance() && 5.f < pActor->Calc_Distance())
	{
		pState = Shoot(pActor, fTimeDelta, _iAnimIndex);
		if (pState)	return pState;
	}
	if (5.f > pActor->Calc_Distance() && 0.5f < pActor->Calc_Distance())
	{
		pState = Attack(pActor, fTimeDelta, _iAnimIndex);
		if (pState)	return pState;
	}
	

	return nullptr;
}

CState<CMagician_GamePlay>* CMagicianDefaultState::WalkandDisappear(CMagician_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	_uint iRandom = rand() % 1;

	switch (iRandom)
	{
	case 0:
		return new CMagician_Walk_Front();
// 	case 1:
// 		return new CMagician_DisappearF();
	}
}

CState<CMagician_GamePlay>* CMagicianDefaultState::Attack(CMagician_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	_uint iRandom = rand() % 3;

	switch (iRandom)
	{
	case 0:
		return new CMagician_Attack1();
	case 1:
		return new CMagician_Attack4();
	case 2:
		return new CMagician_Attack5();
	}

}

CState<CMagician_GamePlay>* CMagicianDefaultState::Shoot(CMagician_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	_uint iRandom = rand() % 3;

	switch (iRandom)
	{
	case 0:
		return new CMagician_Shoot1();
	case 1:
		return new CMagician_Shoot2();
	case 2:
		return new CMagician_Shoot3();
	}
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

