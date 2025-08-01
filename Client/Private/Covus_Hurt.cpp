#include "stdafx.h"
#include "Covus_Hurt.h"



void CCovus_Hurt::Initialize(CCovus_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_IsAttack(true);
}

void CCovus_Hurt::Release(CCovus_GamePlay* pActor)
{
	__super::Release(pActor);
	pActor->Set_IsAttack(false);
}

CState<CCovus_GamePlay>* CCovus_Hurt::Update_State(CCovus_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
