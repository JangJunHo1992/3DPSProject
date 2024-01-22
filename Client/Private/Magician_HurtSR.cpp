#include "stdafx.h"
#include "Magician_HurtSR.h"
#include "GameInstance.h"


void CMagician_HurtSR::Initialize(CMagician_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true, true);
}

CState<CMagician_GamePlay>* CMagician_HurtSR::Update(CMagician_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
	}
	return nullptr;
}

void CMagician_HurtSR::Release(CMagician_GamePlay* pActor)
{
	__super::Release(pActor);
}