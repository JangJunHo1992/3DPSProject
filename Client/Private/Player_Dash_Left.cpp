#include "stdafx.h"
#include "Player_Dash_Left.h"
#include "GameInstance.h"


void CPlayer_Dash_Left::Initialize(CPlayer* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true, true);
}

CState<CPlayer>* CPlayer_Dash_Left::Update(CPlayer* pActor, _float fTimeDelta)
{
	pActor->Go_Left(fTimeDelta);

	return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
}

void CPlayer_Dash_Left::Release(CPlayer* pActor)
{
	__super::Release(pActor);
}