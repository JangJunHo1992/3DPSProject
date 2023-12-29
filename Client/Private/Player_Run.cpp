#include "Player_Run.h"



void CPlayer_Run::Initialize(CPlayer* pActor)
{
	__super::Initialize(pActor);
}

void CPlayer_Run::Release(CPlayer* pActor)
{
	__super::Release(pActor);
}

CState<CPlayer>* CPlayer_Run::Update_State(CPlayer* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
