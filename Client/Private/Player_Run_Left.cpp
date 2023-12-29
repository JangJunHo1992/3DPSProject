#include "stdafx.h"
#include "Player_Run_Left.h"
#include "GameInstance.h"

void CPlayer_Run_Left::Initialize(CPlayer* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true, false);
}

CState<CPlayer>* CPlayer_Run_Left::Update(CPlayer* pActor, _float fTimeDelta)
{
	pActor->Go_Left(fTimeDelta);

	return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
}

void CPlayer_Run_Left::Release(CPlayer* pActor)
{
	__super::Release(pActor);
}