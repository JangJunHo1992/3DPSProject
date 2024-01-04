#include "stdafx.h"
#include "Covus_HurtSL.h"
#include "GameInstance.h"


void CCovus_HurtSL::Initialize(CCovus_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true, true);
}

CState<CCovus_GamePlay>* CCovus_HurtSL::Update(CCovus_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
	}
	return nullptr;
}

void CCovus_HurtSL::Release(CCovus_GamePlay* pActor)
{
	__super::Release(pActor);
}