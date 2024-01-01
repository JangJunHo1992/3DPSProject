#include "stdafx.h"
#include "Player_Run_Back.h"
#include "GameInstance.h"



void CCovus_Run_Back::Initialize(CCovus_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true,false);
}

CState<CCovus_GamePlay>* CCovus_Run_Back::Update(CCovus_GamePlay* pActor, _float fTimeDelta)
{
	pActor->Go_Backward(fTimeDelta);

	return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
}

void CCovus_Run_Back::Release(CCovus_GamePlay* pActor)
{
	__super::Release(pActor);
}