#include "stdafx.h"
#include "Wizard_Hit_Bodystrong_Back.h"
#include "GameInstance.h"

//#include "GreatDualBlade_Attack_02.h"

void CWizard_Hit_Bodystrong_Back::Initialize(CWizard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CWizard_GamePlay>* CWizard_Hit_Bodystrong_Back::Update(CWizard_GamePlay* pActor, _float fTimeDelta)
{
	//if (pActor->Is_Animation_End())
	//{
	//	return new CGreat_DualBlade_Attack_02();
	//}

	return nullptr;
}

void CWizard_Hit_Bodystrong_Back::Release(CWizard_GamePlay* pActor)
{

}