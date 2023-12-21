#include "stdafx.h"
#include "GreatDualBlade_Roll_Left.h"
#include "GameInstance.h"

#include "GreatDualBlade_Roll_Right.h"


void CGreatDualBlade_Roll_Left::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Roll_Left::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Roll_Right();
	}

	return nullptr;
}

void CGreatDualBlade_Roll_Left::Release(CRaider_GamePlay* pActor)
{
	
}