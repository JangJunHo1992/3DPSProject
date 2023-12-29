#include "stdafx.h"
#include "Player_Run_Back.h"
#include "GameInstance.h"


void CPlayer_Run_Back::Initialize(CPlayer* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true, false);
}

CState<CPlayer>* CPlayer_Run_Back::Update(CPlayer* pActor, _float fTimeDelta)
{
	pActor->Go_Backward(fTimeDelta);

	return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
}

void CPlayer_Run_Back::Release(CPlayer* pActor)
{
	__super::Release(pActor);
}