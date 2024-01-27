#include "stdafx.h"
#include "Varg_StartIdle.h"
#include "GameInstance.h"



void CVarg_StartIdle::Initialize(CVarg_GamePlay* pActor)
{
	__super::Initialize(pActor);

	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CVarg_GamePlay>* CVarg_StartIdle::Update(CVarg_GamePlay* pActor, _float fTimeDelta)
{
	
	if (pActor->Is_Animation_End())
	{
		return nullptr;
	}


	return nullptr;
	
}

void CVarg_StartIdle::Release(CVarg_GamePlay* pActor)
{
	__super::Release(pActor);
}