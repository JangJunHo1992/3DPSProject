#include "stdafx.h"
#include "GreatDualBlade_Attack_03.h"
#include "GameInstance.h"

#include "GreatDualBlade_Attack_04.h"

void CGreat_DualBlade_Attack_03::Initialize(CRaider_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreat_DualBlade_Attack_03::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreat_DualBlade_Attack_04();
	}

	return nullptr;
}

void CGreat_DualBlade_Attack_03::Release(CRaider_GamePlay* pActor)
{
	
}