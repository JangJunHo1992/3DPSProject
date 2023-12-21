#include "stdafx.h"
#include "Wizard_Move_Strafe_Run_Right135.h"
#include "GameInstance.h"

//#include "GreatDualBlade_Attack_02.h"

void CWizard_Move_Strafe_Run_Right135::Initialize(CWizard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CWizard_GamePlay>* CWizard_Move_Strafe_Run_Right135::Update(CWizard_GamePlay* pActor, _float fTimeDelta)
{
	//if (pActor->Is_Animation_End())
	//{
	//	return new CGreat_DualBlade_Attack_02();
	//}

	return nullptr;
}

void CWizard_Move_Strafe_Run_Right135::Release(CWizard_GamePlay* pActor)
{

}