#include "stdafx.h"
#include "TwoHandedHammerSet_Pose_Look_LD.h"
#include "GameInstance.h"

//#include "GreatDualBlade_Attack_02.h"

void CTwoHandedHammerSet_Pose_Look_LD::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Pose_Look_LD::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	//if (pActor->Is_Animation_End())
	//{
	//	return new CGreat_DualBlade_Attack_02();
	//}

	return nullptr;
}

void CTwoHandedHammerSet_Pose_Look_LD::Release(CKing_GamePlay* pActor)
{

}