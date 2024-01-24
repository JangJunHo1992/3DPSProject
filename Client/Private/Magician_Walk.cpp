#include "Magician_Walk.h"



void CMagician_Walk::Initialize(CMagician_GamePlay* pActor)
{
	__super::Initialize(pActor);
}

void CMagician_Walk::Release(CMagician_GamePlay* pActor)
{
	__super::Release(pActor);
}

CState<CMagician_GamePlay>* CMagician_Walk::Update_State(CMagician_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
