#include "stdafx.h"
#include "GreatDualBlade_Walk_Front.h"
#include "GameInstance.h"

#include "GreatDualBlade_Walk_Left.h"


void CGreatDualBlade_Walk_Front::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Walk_Front::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Walk_Left();
	}

	return nullptr;
}

void CGreatDualBlade_Walk_Front::Release(CRaider_GamePlay* pActor)
{
	
}