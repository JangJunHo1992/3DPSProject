#include "stdafx.h"
#include "Player_Walk_Left.h"
#include "GameInstance.h"


void CPlayer_Walk_Left::Initialize(CPlayer* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true, false);
}

CState<CPlayer>* CPlayer_Walk_Left::Update(CPlayer* pActor, _float fTimeDelta)
{
	pActor->Go_Left(fTimeDelta);

	return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
}

void CPlayer_Walk_Left::Release(CPlayer* pActor)
{
	__super::Release(pActor);
}