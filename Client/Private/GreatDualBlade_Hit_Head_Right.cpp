#include "stdafx.h"
#include "GreatDualBlade_Hit_Head_Right.h"
#include "GameInstance.h"

#include "GreatDualBlade_Hit_01.h"


void CGreatDualBlade_Hit_Head_Right::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Hit_Head_Right::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Hit_01();
	}

	return nullptr;
}

void CGreatDualBlade_Hit_Head_Right::Release(CRaider_GamePlay* pActor)
{
	
}