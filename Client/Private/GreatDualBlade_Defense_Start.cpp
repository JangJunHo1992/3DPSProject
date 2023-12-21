#include "stdafx.h"
#include "GreatDualBlade_Defense_Start.h"
#include "GameInstance.h"

#include "GreatDualBlade_Defense_Loop.h"


void CGreatDualBlade_Defense_Start::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Defense_Start::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Defense_Loop();
	}

	return nullptr;
}

void CGreatDualBlade_Defense_Start::Release(CRaider_GamePlay* pActor)
{
	
}