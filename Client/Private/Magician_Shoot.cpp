#include "stdafx.h"
#include "Magician_Shoot.h"



void CMagician_Shoot::Initialize(CMagician_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_IsAttack(true);
}

void CMagician_Shoot::Release(CMagician_GamePlay* pActor)
{
	__super::Release(pActor);
	pActor->Set_IsAttack(false);
}

CState<CMagician_GamePlay>* CMagician_Shoot::Update_State(CMagician_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
