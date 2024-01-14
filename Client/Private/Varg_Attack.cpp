#include "stdafx.h"
#include "Varg_Attack.h"



void CVarg_Attack::Initialize(CVarg_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_IsAttack(true);
}

void CVarg_Attack::Release(CVarg_GamePlay* pActor)
{
	__super::Release(pActor);
	pActor->Set_IsAttack(false);
}

CState<CVarg_GamePlay>* CVarg_Attack::Update_State(CVarg_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
