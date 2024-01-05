#include "stdafx.h"
#include "Magician_Idle.h"
#include "GameInstance.h"



void CMagician_Idle::Initialize(CMagician_GamePlay* pActor)
{
	__super::Initialize(pActor);

	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true);
}

CState<CMagician_GamePlay>* CMagician_Idle::Update(CMagician_GamePlay* pActor, _float fTimeDelta)
{
	CState<CMagician_GamePlay>* pState;
	pState = Hitted(pActor, fTimeDelta, g_iAnimIndex);
	if (pState)	return pState;

	return Ground_Normal(pActor, fTimeDelta, g_iAnimIndex);
}

void CMagician_Idle::Release(CMagician_GamePlay* pActor)
{
	__super::Release(pActor);
}