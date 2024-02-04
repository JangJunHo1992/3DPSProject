#include "stdafx.h"
#include "JobMob2_Dead.h"
#include "GameInstance.h"
#include "JobMob2_Idle.h"

void CJobMob2_Dead::Initialize(CJobMob2_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CJobMob2_GamePlay>* CJobMob2_Dead::Update(CJobMob2_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		pActor->Activate_Dissolve();
	}
	
	return nullptr;
}

void CJobMob2_Dead::Release(CJobMob2_GamePlay* pActor)
{
}
