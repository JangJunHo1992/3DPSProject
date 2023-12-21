#include "stdafx.h"
#include "GreatDualBlade_Run_Back.h"
#include "GameInstance.h"

//#include "GreatDualBlade_Run_Front_L45.h"


void CGreatDualBlade_Run_Back::Initialize(CRaider_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true, false);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Run_Back::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	return Run(pActor, fTimeDelta, g_iAnimIndex);
}

void CGreatDualBlade_Run_Back::Release(CRaider_GamePlay* pActor)
{
	__super::Release(pActor);
}