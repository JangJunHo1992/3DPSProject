#include "Player_Walk.h"



void CPlayer_Walk::Initialize(CPlayer* pActor)
{
	__super::Initialize(pActor);
}

void CPlayer_Walk::Release(CPlayer* pActor)
{
	__super::Release(pActor);
}

CState<CPlayer>* CPlayer_Walk::Update_State(CPlayer* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
