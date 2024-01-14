#include "Magician_Disappear.h"

void CMagician_Disappear::Initialize(CMagician_GamePlay* pActor)
{
	__super::Initialize(pActor);
}

void CMagician_Disappear::Release(CMagician_GamePlay* pActor)
{
	__super::Release(pActor);
}

CState<CMagician_GamePlay>* CMagician_Disappear::Update_State(CMagician_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
