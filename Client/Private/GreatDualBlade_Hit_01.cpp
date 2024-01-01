#include "stdafx.h"
#include "GreatDualBlade_Hit_01.h"
#include "GameInstance.h"

#include "GreatDualBlade_Idle.h"


void CGreatDualBlade_Hit_01::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Hit_01::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Idle();
	}

	return nullptr;
}

void CGreatDualBlade_Hit_01::Release(CRaider_GamePlay* pActor)
{
	
}