#include "stdafx.h"
#include "GreatDualBlade_Roll_Back.h"
#include "GameInstance.h"

#include "GreatDualBlade_Roll_Front.h"


void CGreatDualBlade_Roll_Back::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Roll_Back::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Roll_Front();
	}

	return nullptr;
}

void CGreatDualBlade_Roll_Back::Release(CRaider_GamePlay* pActor)
{
	
}