#include "stdafx.h"
#include "GreatDualBlade_Combo_05_03.h"
#include "GameInstance.h"

#include "GreatDualBlade_Combo_05_04.h"


void CGreatDualBlade_Combo_05_03::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Combo_05_03::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Combo_05_04();
	}

	return nullptr;
}

void CGreatDualBlade_Combo_05_03::Release(CRaider_GamePlay* pActor)
{
	
}