#include "stdafx.h"
#include "Player_Walk_Back.h"
#include "GameInstance.h"



void CPlayer_Walk_Back::Initialize(CPlayer* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true,false);
}

CState<CPlayer>* CPlayer_Walk_Back::Update(CPlayer* pActor, _float fTimeDelta)
{
	pActor->Go_Backward(fTimeDelta);

	return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
}

void CPlayer_Walk_Back::Release(CPlayer* pActor)
{
	
}