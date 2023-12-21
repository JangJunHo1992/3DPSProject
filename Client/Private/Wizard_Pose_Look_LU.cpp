#include "stdafx.h"
#include "Wizard_Pose_Look_LU.h"
#include "GameInstance.h"

//#include "GreatDualBlade_Attack_02.h"

void CWizard_Pose_Look_LU::Initialize(CWizard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CWizard_GamePlay>* CWizard_Pose_Look_LU::Update(CWizard_GamePlay* pActor, _float fTimeDelta)
{
	//if (pActor->Is_Animation_End())
	//{
	//	return new CGreat_DualBlade_Attack_02();
	//}

	return nullptr;
}

void CWizard_Pose_Look_LU::Release(CWizard_GamePlay* pActor)
{

}