#include "Varg_Walk.h"



void CVarg_Walk::Initialize(CVarg_GamePlay* pActor)
{
	__super::Initialize(pActor);
}

void CVarg_Walk::Release(CVarg_GamePlay* pActor)
{
	__super::Release(pActor);
}

CState<CVarg_GamePlay>* CVarg_Walk::Update_State(CVarg_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
