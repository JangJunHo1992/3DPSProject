#include "stdafx.h"
#include "GreatDualBlade_Run_Left.h"
#include "GameInstance.h"

//#include "GreatDualBlade_Run_Right.h"


void CGreatDualBlade_Run_Left::Initialize(CRaider_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true, false);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Run_Left::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	pActor->Go_Left(fTimeDelta);

	return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
}

void CGreatDualBlade_Run_Left::Release(CRaider_GamePlay* pActor)
{
	__super::Release(pActor);
}