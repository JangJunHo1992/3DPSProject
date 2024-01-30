#include "stdafx.h"
#include "Magician_Attack.h"



void CMagician_Attack::Initialize(CMagician_GamePlay* pActor)
{
	__super::Initialize(pActor);
	//pActor->Set_IsAttack(true);
}

void CMagician_Attack::Release(CMagician_GamePlay* pActor)
{
	__super::Release(pActor);
	//pActor->Set_IsAttack(false);
}

CState<CMagician_GamePlay>* CMagician_Attack::Update_State(CMagician_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
