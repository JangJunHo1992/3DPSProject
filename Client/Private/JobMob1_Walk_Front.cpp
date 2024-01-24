#include "stdafx.h"
#include "JobMob1_Walk_Front.h"
#include "GameInstance.h"



void CJobMob1_Walk_Front::Initialize(CJobMob1_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true, false);
}

CState<CJobMob1_GamePlay>* CJobMob1_Walk_Front::Update(CJobMob1_GamePlay* pActor, _float fTimeDelta)
{
	pActor->Go_Straight(fTimeDelta * 0.5);

	return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
}

void CJobMob1_Walk_Front::Release(CJobMob1_GamePlay* pActor)
{
	__super::Release(pActor);
}