#include "stdafx.h"
#include "Varg_Stun.h"
#include "GameInstance.h"

void CVarg_Stun::Initialize(CVarg_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);

}

CState<CVarg_GamePlay>* CVarg_Stun::Update(CVarg_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		//return nullptr;
	}


	return nullptr;
}

void CVarg_Stun::Release(CVarg_GamePlay* pActor)
{
}
