#include "stdafx.h"
#include "Covus_Healing.h"
#include "GameInstance.h"
#include "Player_Idle.h"



void CCovus_Healing::Initialize(CCovus_GamePlay* pActor)
{
	__super::Initialize(pActor);

	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CCovus_GamePlay>* CCovus_Healing::Update(CCovus_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CCovus_Idle();
	}

	return nullptr;
}

void CCovus_Healing::Release(CCovus_GamePlay* pActor)
{
	__super::Release(pActor);
}