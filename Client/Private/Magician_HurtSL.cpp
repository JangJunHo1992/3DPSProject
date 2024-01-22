#include "stdafx.h"
#include "Magician_HurtSL.h"
#include "GameInstance.h"


void CMagician_HurtSL::Initialize(CMagician_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true, true);
}

CState<CMagician_GamePlay>* CMagician_HurtSL::Update(CMagician_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
	}
	return nullptr;
}

void CMagician_HurtSL::Release(CMagician_GamePlay* pActor)
{
	__super::Release(pActor);
}