#include "stdafx.h"
#include "GreatDualBlade_Defense.h"
#include "GameInstance.h"

#include "GreatDualBlade_Down_01.h"


void CGreatDualBlade_Defense::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Defense::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Down_01();
	}

	return nullptr;
}

void CGreatDualBlade_Defense::Release(CRaider_GamePlay* pActor)
{
	
}