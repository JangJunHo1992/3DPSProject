#include "Player_Dash.h"



void CPlayer_Dash::Initialize(CPlayer* pActor)
{
	__super::Initialize(pActor);
}

void CPlayer_Dash::Release(CPlayer* pActor)
{
	__super::Release(pActor);
}

CState<CPlayer>* CPlayer_Dash::Update_State(CPlayer* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
