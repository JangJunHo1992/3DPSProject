#include "stdafx.h"
#include "Spear_Shield_Finisher02_A.h"
#include "GameInstance.h"

#include "Spear_Shield_Jump.h"

void CSpear_Shield_Finisher02_A::Initialize(CKnightGuard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKnightGuard_GamePlay>* CSpear_Shield_Finisher02_A::Update(CKnightGuard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CSpear_Shield_Jump();
	}

	return nullptr;
}

void CSpear_Shield_Finisher02_A::Release(CKnightGuard_GamePlay* pActor)
{

}