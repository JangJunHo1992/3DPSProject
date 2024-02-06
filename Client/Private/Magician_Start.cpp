#include "stdafx.h"
#include "Magician_Start.h"
#include "GameInstance.h"
#include "Magician_Idle.h"
#include "Boss_HPBarBase.h"
#include "Boss_HPBar2.h"
#include "Boss_HPBar.h"

void CMagician_Start::Initialize(CMagician_GamePlay* pActor)
{
	__super::Initialize(pActor);

	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CMagician_GamePlay>* CMagician_Start::Update(CMagician_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		CBoss_HPBar::m_bCheckBossHPBar = true;
		pActor->Set_StartScene2(false);
		m_pGameInstance->Play_BGM(L"MAGICIAN",L"Sea_of_Trees_Level_-_Combat.ogg",1.f);
		return new CMagician_Idle();
	}
}

void CMagician_Start::Release(CMagician_GamePlay* pActor)
{
	__super::Release(pActor);
	
}