#include "stdafx.h"
#include "GreatDualBlade_Hit_Head_Left.h"
#include "GameInstance.h"

#include "GreatDualBlade_Hit_Head_Right.h"


void CGreatDualBlade_Hit_Head_Left::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Hit_Head_Left::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Hit_Head_Right();
	}

	return nullptr;
}

void CGreatDualBlade_Hit_Head_Left::Release(CRaider_GamePlay* pActor)
{
	
}