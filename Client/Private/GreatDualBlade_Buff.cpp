#include "stdafx.h"
#include "GreatDualBlade_Buff.h"
#include "GameInstance.h"

#include "GreatDualBlade_Combo_01_01.h"


void CGreatDualBlade_Buff::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Buff::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Combo_01_01();
	}

	return nullptr;
}

void CGreatDualBlade_Buff::Release(CRaider_GamePlay* pActor)
{
	
}