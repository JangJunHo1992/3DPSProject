#include "stdafx.h"
#include "Player_Walk_Front_L45.h"
#include "GameInstance.h"



void CPlayer_Walk_Front_L45::Initialize(CPlayer* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true, false);
}

CState<CPlayer>* CPlayer_Walk_Front_L45::Update(CPlayer* pActor, _float fTimeDelta)
{
	pActor->Go_Straight_L45(fTimeDelta);

	return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
}

void CPlayer_Walk_Front_L45::Release(CPlayer* pActor)
{

}