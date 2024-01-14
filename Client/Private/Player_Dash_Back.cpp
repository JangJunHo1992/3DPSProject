#include "stdafx.h"
#include "Player_Dash_Back.h"
#include "GameInstance.h"


void CCovus_Dash_Back::Initialize(CCovus_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true, true);
}

CState<CCovus_GamePlay>* CCovus_Dash_Back::Update(CCovus_GamePlay* pActor, _float fTimeDelta)
{
	pActor->Go_Backward(fTimeDelta * 0.25);
	if (pActor->Is_Inputable_Back(10))
	{
		return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
	}
	return nullptr;
}

void CCovus_Dash_Back::Release(CCovus_GamePlay* pActor)
{
	__super::Release(pActor);
}