#include "stdafx.h"
#include "Spear_Shield_Attack_Shield05.h"
#include "GameInstance.h"

#include "Spear_Shield_Attack_StingDown.h"

void CSpear_Shield_Attack_Shield05::Initialize(CKnightGuard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKnightGuard_GamePlay>* CSpear_Shield_Attack_Shield05::Update(CKnightGuard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CSpear_Shield_Attack_StingDown();
	}

	return nullptr;
}

void CSpear_Shield_Attack_Shield05::Release(CKnightGuard_GamePlay* pActor)
{

}