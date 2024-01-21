#include "stdafx.h"
#include "JobMob2_Hurt.h"



void CJobMob2_Hurt::Initialize(CJobMob2_GamePlay* pActor)
{
	__super::Initialize(pActor);
}

void CJobMob2_Hurt::Release(CJobMob2_GamePlay* pActor)
{
	__super::Release(pActor);
}

CState<CJobMob2_GamePlay>* CJobMob2_Hurt::Update_State(CJobMob2_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
