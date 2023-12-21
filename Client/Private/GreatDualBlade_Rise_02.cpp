#include "stdafx.h"
#include "GreatDualBlade_Rise_02.h"
#include "GameInstance.h"

#include "GreatDualBlade_Rise_Left_Up.h"


void CGreatDualBlade_Rise_02::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Rise_02::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Rise_Left_Up();
	}

	return nullptr;
}

void CGreatDualBlade_Rise_02::Release(CRaider_GamePlay* pActor)
{
	
}