#include "stdafx.h"
#include "Magician_Stun.h"
#include "GameInstance.h"


void CMagician_Stun::Initialize(CMagician_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CMagician_GamePlay>* CMagician_Stun::Update(CMagician_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return nullptr;
	}


	return nullptr;
}

void CMagician_Stun::Release(CMagician_GamePlay* pActor)
{
	__super::Release(pActor);
}
