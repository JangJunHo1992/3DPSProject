#include "stdafx.h"
#include "Player_Walk_Right.h"
#include "GameInstance.h"


void CCovus_Walk_Right::Initialize(CCovus_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true, false);
}

CState<CCovus_GamePlay>* CCovus_Walk_Right::Update(CCovus_GamePlay* pActor, _float fTimeDelta)
{
	pActor->Go_Right(fTimeDelta * 0.5);

	return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
}

void CCovus_Walk_Right::Release(CCovus_GamePlay* pActor)
{
	__super::Release(pActor);
}