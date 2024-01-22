#include "stdafx.h"
#include "JobMob2_Idle.h"
#include "GameInstance.h"



void CJobMob2_Idle::Initialize(CJobMob2_GamePlay* pActor)
{
	__super::Initialize(pActor);

	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true);
}

CState<CJobMob2_GamePlay>* CJobMob2_Idle::Update(CJobMob2_GamePlay* pActor, _float fTimeDelta)
{
	CState<CJobMob2_GamePlay>* pState;
	pState = Hitted(pActor, fTimeDelta, g_iAnimIndex);
	if (pState)	return pState;

	return Ground_Normal(pActor, fTimeDelta, g_iAnimIndex);
}

void CJobMob2_Idle::Release(CJobMob2_GamePlay* pActor)
{
	__super::Release(pActor);
}