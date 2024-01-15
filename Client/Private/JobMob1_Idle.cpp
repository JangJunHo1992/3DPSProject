#include "stdafx.h"
#include "JobMob1_Idle.h"
#include "GameInstance.h"



void CJobMob1_Idle::Initialize(CJobMob1_GamePlay* pActor)
{
	__super::Initialize(pActor);

	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true);
}

CState<CJobMob1_GamePlay>* CJobMob1_Idle::Update(CJobMob1_GamePlay* pActor, _float fTimeDelta)
{
	CState<CJobMob1_GamePlay>* pState;
	pState = Hitted(pActor, fTimeDelta, g_iAnimIndex);
	if (pState)	return pState;

	return Ground_Normal(pActor, fTimeDelta, g_iAnimIndex);
}

void CJobMob1_Idle::Release(CJobMob1_GamePlay* pActor)
{
	__super::Release(pActor);
}