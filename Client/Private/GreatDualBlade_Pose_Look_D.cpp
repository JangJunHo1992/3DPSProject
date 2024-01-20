#include "stdafx.h"
#include "GreatDualBlade_Pose_Look_D.h"
#include "GameInstance.h"

#include "GreatDualBlade_Pose_Look_LD.h"


void CGreatDualBlade_Pose_Look_D::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Pose_Look_D::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Pose_Look_LD();
	}

	return nullptr;
}

void CGreatDualBlade_Pose_Look_D::Release(CRaider_GamePlay* pActor)
{
	
}