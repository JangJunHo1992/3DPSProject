#include "stdafx.h"
#include "Spear_Shield_Victim_Idle.h"
#include "GameInstance.h"

#include "Spear_Shield_Attacker_Idle.h"

void CSpear_Shield_Victim_Idle::Initialize(CKnightGuard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKnightGuard_GamePlay>* CSpear_Shield_Victim_Idle::Update(CKnightGuard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CSpear_Shield_Attacker_Idle();
	}

	return nullptr;
}

void CSpear_Shield_Victim_Idle::Release(CKnightGuard_GamePlay* pActor)
{

}