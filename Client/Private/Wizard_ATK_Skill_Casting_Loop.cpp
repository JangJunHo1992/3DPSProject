#include "stdafx.h"
#include "Wizard_ATK_Skill_Casting_Loop.h"
#include "GameInstance.h"

#include "Wizard_ATK_Skill_Casting_End.h"

void CWizard_ATK_Skill_Casting_Loop::Initialize(CWizard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CWizard_GamePlay>* CWizard_ATK_Skill_Casting_Loop::Update(CWizard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CWizard_ATK_Skill_Casting_End();
	}

	return nullptr;
}

void CWizard_ATK_Skill_Casting_Loop::Release(CWizard_GamePlay* pActor)
{

}