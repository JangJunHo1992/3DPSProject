#include "stdafx.h"
#include "JobMob2_Walk_Front.h"
#include "GameInstance.h"



void CJobMob2_Walk_Front::Initialize(CJobMob2_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true, false);
}

CState<CJobMob2_GamePlay>* CJobMob2_Walk_Front::Update(CJobMob2_GamePlay* pActor, _float fTimeDelta)
{
	pActor->Go_Straight(fTimeDelta * 0.5);

	return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
}

void CJobMob2_Walk_Front::Release(CJobMob2_GamePlay* pActor)
{
	__super::Release(pActor);
}