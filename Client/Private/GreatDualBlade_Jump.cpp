#include "stdafx.h"
#include "GreatDualBlade_Jump.h"
#include "GameInstance.h"

#include "GreatDualBlade_Pose_Look_C.h"


void CGreatDualBlade_Jump::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Jump::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Pose_Look_C();
	}

	return nullptr;
}

void CGreatDualBlade_Jump::Release(CRaider_GamePlay* pActor)
{
	
}