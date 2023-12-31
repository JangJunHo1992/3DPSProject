#include "stdafx.h"
#include "Player_Walk_Front.h"
#include "GameInstance.h"


void CCovus_Walk_Front::Initialize(CCovus_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true, false);
}

CState<CCovus_GamePlay>* CCovus_Walk_Front::Update(CCovus_GamePlay* pActor, _float fTimeDelta)
{
	pActor->Go_Straight(fTimeDelta);

	return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
}

void CCovus_Walk_Front::Release(CCovus_GamePlay* pActor)
{
	__super::Release(pActor);
}