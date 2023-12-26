#include "stdafx.h"
#include "GreatDualBlade_Run_Back_R45.h"
#include "GameInstance.h"

//#include "GreatDualBlade_Run_Back.h"


void CGreatDualBlade_Run_Back_R45::Initialize(CRaider_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true, false);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Run_Back_R45::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	pActor->Go_Backward_R45(fTimeDelta);

	return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
}

void CGreatDualBlade_Run_Back_R45::Release(CRaider_GamePlay* pActor)
{
	__super::Release(pActor);
}