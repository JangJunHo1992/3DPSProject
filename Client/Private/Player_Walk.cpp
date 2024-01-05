#include "Player_Walk.h"



void CCovus_Walk::Initialize(CCovus_GamePlay* pActor)
{
	__super::Initialize(pActor);
}

void CCovus_Walk::Release(CCovus_GamePlay* pActor)
{
	__super::Release(pActor);
}

CState<CCovus_GamePlay>* CCovus_Walk::Update_State(CCovus_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
