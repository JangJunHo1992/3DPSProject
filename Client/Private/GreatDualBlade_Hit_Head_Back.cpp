#include "stdafx.h"
#include "GreatDualBlade_Hit_Head_Back.h"
#include "GameInstance.h"

#include "GreatDualBlade_Hit_Head_Front.h"


void CGreatDualBlade_Hit_Head_Back::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Hit_Head_Back::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Hit_Head_Front();
	}

	return nullptr;
}

void CGreatDualBlade_Hit_Head_Back::Release(CRaider_GamePlay* pActor)
{
	
}