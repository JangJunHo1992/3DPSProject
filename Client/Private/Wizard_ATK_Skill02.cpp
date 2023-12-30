#include "stdafx.h"
#include "Wizard_ATK_Skill02.h"
#include "GameInstance.h"

#include "Wizard_ATK_Skill03.h"

void CWizard_ATK_Skill02::Initialize(CWizard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CWizard_GamePlay>* CWizard_ATK_Skill02::Update(CWizard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CWizard_ATK_Skill03();
	}

	return nullptr;
}

void CWizard_ATK_Skill02::Release(CWizard_GamePlay* pActor)
{

}