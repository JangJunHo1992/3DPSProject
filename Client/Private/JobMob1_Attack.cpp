#include "stdafx.h"
#include "JobMob1_Attack.h"



void CJobMob1_Attack::Initialize(CJobMob1_GamePlay* pActor)
{
	__super::Initialize(pActor);
	//pActor->Set_IsAttack(true);
}

void CJobMob1_Attack::Release(CJobMob1_GamePlay* pActor)
{
	__super::Release(pActor);
	//pActor->Set_IsAttack(false);
}

CState<CJobMob1_GamePlay>* CJobMob1_Attack::Update_State(CJobMob1_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
