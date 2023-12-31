#include "stdafx.h"
#include "Wizard_ATK_Skill15.h"
#include "GameInstance.h"

#include "Wizard_ATK_Skill16.h"

void CWizard_ATK_Skill15::Initialize(CWizard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CWizard_GamePlay>* CWizard_ATK_Skill15::Update(CWizard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CWizard_ATK_Skill16();
	}

	return nullptr;
}

void CWizard_ATK_Skill15::Release(CWizard_GamePlay* pActor)
{

}