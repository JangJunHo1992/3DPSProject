#include "stdafx.h"
#include "GreatDualBlade_Attack_02.h"
#include "GameInstance.h"

#include "GreatDualBlade_Attack_03.h"


void CGreat_DualBlade_Attack_02::Initialize(CRaider_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreat_DualBlade_Attack_02::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreat_DualBlade_Attack_03();
	}

	return nullptr;
}

void CGreat_DualBlade_Attack_02::Release(CRaider_GamePlay* pActor)
{
	
}