#include "stdafx.h"
#include "Player_Walk_Back_R45.h"
#include "GameInstance.h"



void CPlayer_Walk_Back_R45::Initialize(CPlayer* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true, false);
}

CState<CPlayer>* CPlayer_Walk_Back_R45::Update(CPlayer* pActor, _float fTimeDelta)
{
	pActor->Go_Backward_R45(fTimeDelta);

	return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
}

void CPlayer_Walk_Back_R45::Release(CPlayer* pActor)
{

}