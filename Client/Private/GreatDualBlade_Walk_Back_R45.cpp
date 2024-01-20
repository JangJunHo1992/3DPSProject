#include "stdafx.h"
#include "GreatDualBlade_Walk_Back_R45.h"
#include "GameInstance.h"

#include "GreatDualBlade_Walk_Back.h"


void CGreatDualBlade_Walk_Back_R45::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Walk_Back_R45::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Walk_Back();
	}

	return nullptr;
}

void CGreatDualBlade_Walk_Back_R45::Release(CRaider_GamePlay* pActor)
{
	
}