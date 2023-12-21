#include "stdafx.h"
#include "GreatDualBlade_Defense_End.h"
#include "GameInstance.h"

#include "GreatDualBlade_Defense.h"


void CGreatDualBlade_Defense_End::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Defense_End::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Defense();
	}

	return nullptr;
}

void CGreatDualBlade_Defense_End::Release(CRaider_GamePlay* pActor)
{
	
}