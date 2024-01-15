#include "stdafx.h"
#include "JobMob1_Hurt.h"



void CJobMob1_Hurt::Initialize(CJobMob1_GamePlay* pActor)
{
	__super::Initialize(pActor);
}

void CJobMob1_Hurt::Release(CJobMob1_GamePlay* pActor)
{
	__super::Release(pActor);
}

CState<CJobMob1_GamePlay>* CJobMob1_Hurt::Update_State(CJobMob1_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
