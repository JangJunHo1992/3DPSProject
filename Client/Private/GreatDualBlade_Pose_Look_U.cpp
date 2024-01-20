#include "stdafx.h"
#include "GreatDualBlade_Pose_Look_U.h"
#include "GameInstance.h"

#include "GreatDualBlade_Pose_Look_RU.h"


void CGreatDualBlade_Pose_Look_U::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Pose_Look_U::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()) 
	{
		return new CGreatDualBlade_Pose_Look_RU();
	}

	return nullptr;
}

void CGreatDualBlade_Pose_Look_U::Release(CRaider_GamePlay* pActor)
{
	
}