#include "stdafx.h"
#include "Wizard_ATK_Skill18.h"
#include "GameInstance.h"

#include "Wizard_ATK_Skill19.h"

void CWizard_ATK_Skill18::Initialize(CWizard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CWizard_GamePlay>* CWizard_ATK_Skill18::Update(CWizard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CWizard_ATK_Skill19();
	}

	return nullptr;
}

void CWizard_ATK_Skill18::Release(CWizard_GamePlay* pActor)
{

}