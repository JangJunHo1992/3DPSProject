#include "stdafx.h"
#include "GreatDualBlade_Pose_Look_R.h"
#include "GameInstance.h"

#include "GreatDualBlade_Walk_Back_L45.h"


void CGreatDualBlade_Pose_Look_R::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Pose_Look_R::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Walk_Back_L45();
	}

	return nullptr;
}

void CGreatDualBlade_Pose_Look_R::Release(CRaider_GamePlay* pActor)
{
	
}