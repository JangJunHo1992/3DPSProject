#include "stdafx.h"
#include "Player_Walk_Back_R45.h"
#include "GameInstance.h"



void CCovus_Walk_Back_R45::Initialize(CCovus_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true, false);
}

CState<CCovus_GamePlay>* CCovus_Walk_Back_R45::Update(CCovus_GamePlay* pActor, _float fTimeDelta)
{
	pActor->Go_Backward_R45(fTimeDelta * 0.5);

	return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
}

void CCovus_Walk_Back_R45::Release(CCovus_GamePlay* pActor)
{
	__super::Release(pActor);
}