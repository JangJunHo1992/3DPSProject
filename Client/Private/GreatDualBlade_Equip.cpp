#include "stdafx.h"
#include "GreatDualBlade_Equip.h"
#include "GameInstance.h"

#include "GreatDualBlade_Hit_Head_Back.h"


void CGreatDualBlade_Equip::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Equip::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Hit_Head_Back();
	}

	return nullptr;
}

void CGreatDualBlade_Equip::Release(CRaider_GamePlay* pActor)
{
	
}