#include "stdafx.h"
#include "Wizard_ATK_Skill10.h"
#include "GameInstance.h"

//#include "GreatDualBlade_Attack_02.h"

void CWizard_ATK_Skill10::Initialize(CWizard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CWizard_GamePlay>* CWizard_ATK_Skill10::Update(CWizard_GamePlay* pActor, _float fTimeDelta)
{
	//if (pActor->Is_Animation_End())
	//{
	//	return new CGreat_DualBlade_Attack_02();
	//}

	return nullptr;
}

void CWizard_ATK_Skill10::Release(CWizard_GamePlay* pActor)
{

}