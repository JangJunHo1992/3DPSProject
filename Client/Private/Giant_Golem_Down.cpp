#include "stdafx.h"
#include "Giant_Golem_Down.h"
#include "GameInstance.h"

#include "Giant_Golem_Rise.h"

void CGiant_Golem_Down::Initialize(CGolem_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CGolem_GamePlay>* CGiant_Golem_Down::Update(CGolem_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CGiant_Golem_Rise();
	}

	return nullptr;
}

void CGiant_Golem_Down::Release(CGolem_GamePlay* pActor)
{

}