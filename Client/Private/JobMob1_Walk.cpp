#include "JobMob1_Walk.h"



void CJobMob1_Walk::Initialize(CJobMob1_GamePlay* pActor)
{
	__super::Initialize(pActor);
}

void CJobMob1_Walk::Release(CJobMob1_GamePlay* pActor)
{
	__super::Release(pActor);
}

CState<CJobMob1_GamePlay>* CJobMob1_Walk::Update_State(CJobMob1_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
