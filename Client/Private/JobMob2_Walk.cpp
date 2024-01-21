#include "JobMob2_Walk.h"



void CJobMob2_Walk::Initialize(CJobMob2_GamePlay* pActor)
{
	__super::Initialize(pActor);
}

void CJobMob2_Walk::Release(CJobMob2_GamePlay* pActor)
{
	__super::Release(pActor);
}

CState<CJobMob2_GamePlay>* CJobMob2_Walk::Update_State(CJobMob2_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
