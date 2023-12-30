#include "stdafx.h"
#include "Wizard_ATK_Skill_Casting_Start.h"
#include "GameInstance.h"

#include "Wizard_ATK_Skill_Casting_Loop.h"

void CWizard_ATK_Skill_Casting_Start::Initialize(CWizard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CWizard_GamePlay>* CWizard_ATK_Skill_Casting_Start::Update(CWizard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CWizard_ATK_Skill_Casting_Loop();
	}

	return nullptr;
}

void CWizard_ATK_Skill_Casting_Start::Release(CWizard_GamePlay* pActor)
{

}