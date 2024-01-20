#include "stdafx.h"
#include "GreatDualBlade_Unequip.h"
#include "GameInstance.h"

#include "GreatDualBlade_Equip.h"


void CGreatDualBlade_Unequip::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Unequip::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Equip();
	}

	return nullptr;
}

void CGreatDualBlade_Unequip::Release(CRaider_GamePlay* pActor)
{
	
}