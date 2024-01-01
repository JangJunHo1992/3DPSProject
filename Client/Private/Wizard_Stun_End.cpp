#include "stdafx.h"
#include "Wizard_Stun_End.h"
#include "GameInstance.h"

#include "Wizard_Idle00.h"

void CWizard_Stun_End::Initialize(CWizard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CWizard_GamePlay>* CWizard_Stun_End::Update(CWizard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CWizard_Idle00();
	}

	return nullptr;
}

void CWizard_Stun_End::Release(CWizard_GamePlay* pActor)
{

}