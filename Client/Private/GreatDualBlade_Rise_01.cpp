#include "stdafx.h"
#include "GreatDualBlade_Rise_01.h"
#include "GameInstance.h"

#include "GreatDualBlade_Rise_02.h"


void CGreatDualBlade_Rise_01::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Rise_01::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Rise_02();
	}

	return nullptr;
}

void CGreatDualBlade_Rise_01::Release(CRaider_GamePlay* pActor)
{
	
}