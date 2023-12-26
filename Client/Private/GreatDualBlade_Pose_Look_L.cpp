#include "stdafx.h"
#include "GreatDualBlade_Pose_Look_L.h"
#include "GameInstance.h"

#include "GreatDualBlade_Pose_Look_U.h"


void CGreatDualBlade_Pose_Look_L::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Pose_Look_L::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Pose_Look_U();
	}

	return nullptr;
}

void CGreatDualBlade_Pose_Look_L::Release(CRaider_GamePlay* pActor)
{
	
}