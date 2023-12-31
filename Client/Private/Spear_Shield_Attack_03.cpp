#include "stdafx.h"
#include "Spear_Shield_Attack_03.h"
#include "GameInstance.h"

#include "Spear_Shield_Attack_04.h"

void CSpear_Shield_Attack_03::Initialize(CKnightGuard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKnightGuard_GamePlay>* CSpear_Shield_Attack_03::Update(CKnightGuard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CSpear_Shield_Attack_04();
	}

	return nullptr;
}

void CSpear_Shield_Attack_03::Release(CKnightGuard_GamePlay* pActor)
{

}