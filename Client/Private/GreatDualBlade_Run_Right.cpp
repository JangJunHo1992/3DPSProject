#include "stdafx.h"
#include "GreatDualBlade_Run_Right.h"
#include "GameInstance.h"

void CGreatDualBlade_Run_Right::Initialize(CRaider_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true, false);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Run_Right::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	pActor->Go_Right(fTimeDelta);

	return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
}

void CGreatDualBlade_Run_Right::Release(CRaider_GamePlay* pActor)
{
	__super::Release(pActor);
}