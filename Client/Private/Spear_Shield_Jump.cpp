#include "stdafx.h"
#include "Spear_Shield_Jump.h"
#include "GameInstance.h"

#include "Spear_Shield_Rise_01.h"

void CSpear_Shield_Jump::Initialize(CKnightGuard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKnightGuard_GamePlay>* CSpear_Shield_Jump::Update(CKnightGuard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CSpear_Shield_Rise_01();
	}

	return nullptr;
}

void CSpear_Shield_Jump::Release(CKnightGuard_GamePlay* pActor)
{

}