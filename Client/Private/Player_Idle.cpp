#include "stdafx.h"
#include "Player_Idle.h"
#include "GameInstance.h"



void CCovus_Idle::Initialize(CCovus_GamePlay* pActor)
{
	__super::Initialize(pActor);

	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true);
}

CState<CCovus_GamePlay>* CCovus_Idle::Update(CCovus_GamePlay* pActor, _float fTimeDelta)
{
	CState<CCovus_GamePlay>* pState;
	pState = Hitted(pActor, fTimeDelta, g_iAnimIndex);
	if (pState)	return pState;

	return Ground_Normal(pActor, fTimeDelta, g_iAnimIndex);
}

void CCovus_Idle::Release(CCovus_GamePlay* pActor)
{
	__super::Release(pActor);
}