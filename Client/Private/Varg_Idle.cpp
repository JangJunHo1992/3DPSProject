#include "stdafx.h"
#include "Varg_Idle.h"
#include "GameInstance.h"



void CVarg_Idle::Initialize(CVarg_GamePlay* pActor)
{
	__super::Initialize(pActor);

	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true);
}

CState<CVarg_GamePlay>* CVarg_Idle::Update(CVarg_GamePlay* pActor, _float fTimeDelta)
{
	CState<CVarg_GamePlay>* pState;
	pState = Hitted(pActor, fTimeDelta, g_iAnimIndex);
	if (pState)	return pState;

	return Ground_Normal(pActor, fTimeDelta, g_iAnimIndex);
}

void CVarg_Idle::Release(CVarg_GamePlay* pActor)
{
	__super::Release(pActor);
}