#include "stdafx.h"
#include "Player_Dash_Right.h"
#include "GameInstance.h"


void CPlayer_Dash_Right::Initialize(CPlayer* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true, true);
}

CState<CPlayer>* CPlayer_Dash_Right::Update(CPlayer* pActor, _float fTimeDelta)
{
	pActor->Go_Right(fTimeDelta);

	return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
}

void CPlayer_Dash_Right::Release(CPlayer* pActor)
{
	__super::Release(pActor);
}