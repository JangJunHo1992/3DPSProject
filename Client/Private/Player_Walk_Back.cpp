#include "stdafx.h"
#include "Player_Walk_Back.h"
#include "GameInstance.h"



void CCovus_Walk_Back::Initialize(CCovus_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true,false);
}

CState<CCovus_GamePlay>* CCovus_Walk_Back::Update(CCovus_GamePlay* pActor, _float fTimeDelta)
{
	pActor->Go_Backward(fTimeDelta*0.5);

	return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
}

void CCovus_Walk_Back::Release(CCovus_GamePlay* pActor)
{
	__super::Release(pActor);
}