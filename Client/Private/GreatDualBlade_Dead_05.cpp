#include "stdafx.h"
#include "GreatDualBlade_Dead_05.h"
#include "GameInstance.h"

#include "GreatDualBlade_Defense_Start.h"


void CGreatDualBlade_Dead_05::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Dead_05::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Defense_Start();
	}

	return nullptr;
}

void CGreatDualBlade_Dead_05::Release(CRaider_GamePlay* pActor)
{
	
}