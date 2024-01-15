#include "stdafx.h"
#include "JobMob2_Attack.h"



void CJobMob2_Attack::Initialize(CJobMob2_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_IsAttack(true);
}

void CJobMob2_Attack::Release(CJobMob2_GamePlay* pActor)
{
	__super::Release(pActor);
	pActor->Set_IsAttack(false);
}

CState<CJobMob2_GamePlay>* CJobMob2_Attack::Update_State(CJobMob2_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
