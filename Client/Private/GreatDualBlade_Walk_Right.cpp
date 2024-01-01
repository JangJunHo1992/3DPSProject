#include "stdafx.h"
#include "GreatDualBlade_Walk_Right.h"
#include "GameInstance.h"

#include "GreatDualBlade_Run_Back_L45.h"


void CGreatDualBlade_Walk_Right::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Walk_Right::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Run_Back_L45();
	}

	return nullptr;
}

void CGreatDualBlade_Walk_Right::Release(CRaider_GamePlay* pActor)
{
	
}