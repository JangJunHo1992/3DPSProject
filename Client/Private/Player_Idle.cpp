#include "stdafx.h"
#include "Player_Idle.h"
#include "GameInstance.h"



void CPlayer_Idle::Initialize(CPlayer* pActor)
{
	__super::Initialize(pActor);

	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true);
}

CState<CPlayer>* CPlayer_Idle::Update(CPlayer* pActor, _float fTimeDelta)
{
	CState<CPlayer>* pState;
	pState = Hitted(pActor, fTimeDelta, g_iAnimIndex);
	if (pState)	return pState;

	return Ground_Normal(pActor, fTimeDelta, g_iAnimIndex);
}

void CPlayer_Idle::Release(CPlayer* pActor)
{
	__super::Release(pActor);
}