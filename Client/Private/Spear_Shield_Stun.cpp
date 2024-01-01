#include "stdafx.h"
#include "Spear_Shield_Stun.h"
#include "GameInstance.h"

#include "Spear_Shield_Throw_Spear01.h"

void CSpear_Shield_Stun::Initialize(CKnightGuard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKnightGuard_GamePlay>* CSpear_Shield_Stun::Update(CKnightGuard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CSpear_Shield_Throw_Spear01();
	}

	return nullptr;
}

void CSpear_Shield_Stun::Release(CKnightGuard_GamePlay* pActor)
{

}