#include "stdafx.h"
#include "Giant_Golem_Atk_Throwstone.h"
#include "GameInstance.h"

#include "Giant_Golem_Atk_Whirlwind.h"

void CGiant_Golem_Atk_Throwstone::Initialize(CGolem_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CGolem_GamePlay>* CGiant_Golem_Atk_Throwstone::Update(CGolem_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CGiant_Golem_Atk_Whirlwind();
	}

	return nullptr;
}

void CGiant_Golem_Atk_Throwstone::Release(CGolem_GamePlay* pActor)
{

}