#include "stdafx.h"
#include "GreatDualBlade_Combo_02_04.h"
#include "GameInstance.h"

#include "GreatDualBlade_Combo_03_01.h"


void CGreatDualBlade_Combo_02_04::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Combo_02_04::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Combo_03_01();
	}

	return nullptr;
}

void CGreatDualBlade_Combo_02_04::Release(CRaider_GamePlay* pActor)
{
	
}