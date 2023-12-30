#include "stdafx.h"
#include "Giant_Golem_Atk_Ground.h"
#include "GameInstance.h"

#include "Giant_Golem_Atk_Ground02.h"

void CGiant_Golem_Atk_Ground::Initialize(CGolem_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CGolem_GamePlay>* CGiant_Golem_Atk_Ground::Update(CGolem_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CGiant_Golem_Atk_Ground02();
	}

	return nullptr;
}

void CGiant_Golem_Atk_Ground::Release(CGolem_GamePlay* pActor)
{

}