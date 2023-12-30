#include "stdafx.h"
#include "GreatDualBlade_Attack_04.h"
#include "GameInstance.h"

#include "GreatDualBlade_Avoid_Back.h"


void CGreat_DualBlade_Attack_04::Initialize(CRaider_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreat_DualBlade_Attack_04::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Avoid_Back();
	}

	return nullptr;
}

void CGreat_DualBlade_Attack_04::Release(CRaider_GamePlay* pActor)
{
	
}