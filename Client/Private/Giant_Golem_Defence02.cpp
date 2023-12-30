#include "stdafx.h"
#include "Giant_Golem_Defence02.h"
#include "GameInstance.h"

#include "Giant_Golem_Defence03.h"

void CGiant_Golem_Defence02::Initialize(CGolem_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CGolem_GamePlay>* CGiant_Golem_Defence02::Update(CGolem_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CGiant_Golem_Defence03();
	}

	return nullptr;
}

void CGiant_Golem_Defence02::Release(CGolem_GamePlay* pActor)
{

}