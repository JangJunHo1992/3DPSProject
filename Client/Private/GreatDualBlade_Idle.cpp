#include "stdafx.h"
#include "GreatDualBlade_Idle.h"
#include "GameInstance.h"



void CGreatDualBlade_Idle::Initialize(CRaider_GamePlay* pActor)
{
	__super::Initialize(pActor);

	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Idle::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	return Run(pActor, fTimeDelta, g_iAnimIndex);
}

void CGreatDualBlade_Idle::Release(CRaider_GamePlay* pActor)
{
	__super::Release(pActor);
}