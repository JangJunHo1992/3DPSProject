#include "stdafx.h"
#include "Wizard_Hit_Body_Front.h"
#include "GameInstance.h"

#include "Wizard_ATK_Skill01.h"

void CWizard_Hit_Body_Front::Initialize(CWizard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CWizard_GamePlay>* CWizard_Hit_Body_Front::Update(CWizard_GamePlay* pActor, _float fTimeDelta)
{
	pActor->Knockback(fTimeDelta);
	if (pActor->Is_Animation_End())
	{
		return new CWizard_ATK_Skill01();
	}

	return nullptr;
}

void CWizard_Hit_Body_Front::Release(CWizard_GamePlay* pActor)
{

}