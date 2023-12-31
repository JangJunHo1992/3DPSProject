#include "stdafx.h"
#include "Spear_Shield_Throw_Spear01.h"
#include "GameInstance.h"

#include "Spear_Shield_Victim_Idle.h"

void CSpear_Shield_Throw_Spear01::Initialize(CKnightGuard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKnightGuard_GamePlay>* CSpear_Shield_Throw_Spear01::Update(CKnightGuard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CSpear_Shield_Victim_Idle();
	}

	return nullptr;
}

void CSpear_Shield_Throw_Spear01::Release(CKnightGuard_GamePlay* pActor)
{

}