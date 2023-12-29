#include "stdafx.h"
#include "Player_Dash_Front.h"
#include "GameInstance.h"


void CPlayer_Dash_Front::Initialize(CPlayer* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true, true);
}

CState<CPlayer>* CPlayer_Dash_Front::Update(CPlayer* pActor, _float fTimeDelta)
{
	//pActor->Go_Straight(fTimeDelta);
	if (pActor->Is_Animation_End())
	{
		return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
	}
	return nullptr;
}

void CPlayer_Dash_Front::Release(CPlayer* pActor)
{
	__super::Release(pActor);
}