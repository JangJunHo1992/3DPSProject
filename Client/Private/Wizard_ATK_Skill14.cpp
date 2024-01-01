#include "stdafx.h"
#include "Wizard_ATK_Skill14.h"
#include "GameInstance.h"

#include "Wizard_ATK_Skill15.h"

void CWizard_ATK_Skill14::Initialize(CWizard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CWizard_GamePlay>* CWizard_ATK_Skill14::Update(CWizard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CWizard_ATK_Skill15();
	}

	return nullptr;
}

void CWizard_ATK_Skill14::Release(CWizard_GamePlay* pActor)
{

}