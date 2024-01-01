#include "stdafx.h"
#include "Giant_Golem_Atk_L_foot.h"
#include "GameInstance.h"

#include "Giant_Golem_Atk_R_foot.h"

void CGiant_Golem_Atk_L_foot::Initialize(CGolem_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CGolem_GamePlay>* CGiant_Golem_Atk_L_foot::Update(CGolem_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CGiant_Golem_Atk_R_foot();
	}

	return nullptr;
}

void CGiant_Golem_Atk_L_foot::Release(CGolem_GamePlay* pActor)
{

}