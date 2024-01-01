#include "stdafx.h"
#include "Giant_Golem_Hit_Light_Front.h"
#include "GameInstance.h"

#include "Giant_Golem_Atk_Dash.h"

void CGiant_Golem_Hit_Light_Front::Initialize(CGolem_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CGolem_GamePlay>* CGiant_Golem_Hit_Light_Front::Update(CGolem_GamePlay* pActor, _float fTimeDelta)
{
	//pActor->Knockback(fTimeDelta);
	if (pActor->Is_Animation_End())
	{
		return new CGiant_Golem_Atk_Dash();
	}

	return nullptr;
}

void CGiant_Golem_Hit_Light_Front::Release(CGolem_GamePlay* pActor)
{

}