#include "Player_Run.h"



void CCovus_Run::Initialize(CCovus_GamePlay* pActor)
{
	__super::Initialize(pActor);
}

void CCovus_Run::Release(CCovus_GamePlay* pActor)
{
	__super::Release(pActor);
}

CState<CCovus_GamePlay>* CCovus_Run::Update_State(CCovus_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
