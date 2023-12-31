#include "stdafx.h"
#include "Spear_Shield_Attack_Shield.h"
#include "GameInstance.h"

#include "Spear_Shield_Attack_Shield02.h"

void CSpear_Shield_Attack_Shield::Initialize(CKnightGuard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKnightGuard_GamePlay>* CSpear_Shield_Attack_Shield::Update(CKnightGuard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CSpear_Shield_Attack_Shield02();
	}

	return nullptr;
}

void CSpear_Shield_Attack_Shield::Release(CKnightGuard_GamePlay* pActor)
{

}