#include "stdafx.h"
#include "Magician_Hurt.h"



void CMagician_Hurt::Initialize(CMagician_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_IsAttack(true);
}

void CMagician_Hurt::Release(CMagician_GamePlay* pActor)
{
	__super::Release(pActor);
	pActor->Set_IsAttack(false);
}

CState<CMagician_GamePlay>* CMagician_Hurt::Update_State(CMagician_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
