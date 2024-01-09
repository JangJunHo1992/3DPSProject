#include "stdafx.h"
#include "Varg_Attack2_2.h"
#include "GameInstance.h"

#include "Varg_Idle.h"

void CVarg_Attack2_2::Initialize(CVarg_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CVarg_GamePlay>* CVarg_Attack2_2::Update(CVarg_GamePlay* pActor, _float fTimeDelta)
{
	_uint iMinimumPlayTime = 15;



	if (pActor->Is_Animation_End())
	{
		return new CVarg_Idle();
	}

	return nullptr;
}

void CVarg_Attack2_2::Release(CVarg_GamePlay* pActor)
{
	__super::Release(pActor);
}

