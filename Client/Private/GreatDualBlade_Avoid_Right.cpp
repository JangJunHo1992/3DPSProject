#include "stdafx.h"
#include "GreatDualBlade_Avoid_Right.h"
#include "GameInstance.h"

#include "GreatDualBlade_Buff.h"


void CGreatDualBlade_Avoid_Right::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Avoid_Right::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Buff();
	}

	return nullptr;
}

void CGreatDualBlade_Avoid_Right::Release(CRaider_GamePlay* pActor)
{
	
}