#include "stdafx.h"
#include "Spear_Shield_Roll_Right.h"
#include "GameInstance.h"

#include "Spear_Shield_Move_Run_Sprint.h"

void CSpear_Shield_Roll_Right::Initialize(CKnightGuard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKnightGuard_GamePlay>* CSpear_Shield_Roll_Right::Update(CKnightGuard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CSpear_Shield_Move_Run_Sprint();
	}

	return nullptr;
}

void CSpear_Shield_Roll_Right::Release(CKnightGuard_GamePlay* pActor)
{

}