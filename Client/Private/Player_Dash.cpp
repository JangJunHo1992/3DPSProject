#include "Player_Dash.h"



void CCovus_Dash::Initialize(CCovus_GamePlay* pActor)
{
	__super::Initialize(pActor);
}

void CCovus_Dash::Release(CCovus_GamePlay* pActor)
{
	__super::Release(pActor);
}

CState<CCovus_GamePlay>* CCovus_Dash::Update_State(CCovus_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
