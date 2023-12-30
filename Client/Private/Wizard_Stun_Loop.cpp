#include "stdafx.h"
#include "Wizard_Stun_Loop.h"
#include "GameInstance.h"

#include "Wizard_Stun_End.h"

void CWizard_Stun_Loop::Initialize(CWizard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CWizard_GamePlay>* CWizard_Stun_Loop::Update(CWizard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CWizard_Stun_End();
	}

	return nullptr;
}

void CWizard_Stun_Loop::Release(CWizard_GamePlay* pActor)
{

}