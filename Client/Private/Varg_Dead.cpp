#include "stdafx.h"
#include "Varg_Dead.h"
#include "GameInstance.h"
#include "Varg_Idle.h"

void CVarg_Dead::Initialize(CVarg_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
	
}

CState<CVarg_GamePlay>* CVarg_Dead::Update(CVarg_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		pActor->Set_isdead(true);
	}


	return nullptr;
}

void CVarg_Dead::Release(CVarg_GamePlay* pActor)
{
}
