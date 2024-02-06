#include "stdafx.h"
#include "Varg_Dead.h"
#include "GameInstance.h"
#include "Varg_Idle.h"
#include "Varg_Dead2.h"
#include "Boss_HPBar.h"
void CVarg_Dead2::Initialize(CVarg_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
	
		
}

CState<CVarg_GamePlay>* CVarg_Dead2::Update(CVarg_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Inputable_Back(70))
	{
		pActor->Activate_Dissolve();
	}
	if (pActor->Is_Animation_End())
	{
		
		pActor->Set_CutSceneDead(false);
		pActor->Set_isdead(true);
		CBoss_HPBar::m_bCheckBossHPBar = false;
	}


	return nullptr;
}

void CVarg_Dead2::Release(CVarg_GamePlay* pActor)
{
}
