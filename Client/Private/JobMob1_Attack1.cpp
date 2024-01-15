#include "stdafx.h"
#include "JobMob1_Attack1.h"
#include "GameInstance.h"


#include "JobMob1_Idle.h"

void CJobMob1_Attack1::Initialize(CJobMob1_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CJobMob1_GamePlay>* CJobMob1_Attack1::Update(CJobMob1_GamePlay* pActor, _float fTimeDelta)
{
	_uint iMinimumPlayTime = 15;


	if (pActor->Is_Animation_End())
	{
		return new CJobMob1_Idle();
	}

	return nullptr;
}

void CJobMob1_Attack1::Release(CJobMob1_GamePlay* pActor)
{
	__super::Release(pActor);
}

