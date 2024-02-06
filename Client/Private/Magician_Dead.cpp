#include "stdafx.h"
#include "Magician_Dead.h"
#include "GameInstance.h"
#include "Magician_Idle.h"
#include "Boss_HPBar.h"

void CMagician_Dead::Initialize(CMagician_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CMagician_GamePlay>* CMagician_Dead::Update(CMagician_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Inputable_Back(50))
	{
		pActor->Activate_Dissolve();
	}
	if (pActor->Is_Animation_End())
	{
		CBoss_HPBar::m_bCheckBossHPBar = false;
		pActor->Set_CutSceneDead2(false);
		pActor->Set_isdead(true);
	}

	return nullptr;
}

void CMagician_Dead::Release(CMagician_GamePlay* pActor)
{
	__super::Release(pActor);

}
