#include "stdafx.h"
#include "Varg_RaidAttack2.h"
#include "GameInstance.h"


#include "Varg_Idle.h"

void CVarg_RaidAttack2::Initialize(CVarg_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CVarg_GamePlay>* CVarg_RaidAttack2::Update(CVarg_GamePlay* pActor, _float fTimeDelta)
{
	_uint iMinimumPlayTime = 15;


	if (pActor->Is_Animation_End())
	{
		return new CVarg_Idle();
	}

	return nullptr;
}

void CVarg_RaidAttack2::Release(CVarg_GamePlay* pActor)
{
	__super::Release(pActor);
}

