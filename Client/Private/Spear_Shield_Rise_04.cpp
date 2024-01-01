#include "stdafx.h"
#include "Spear_Shield_Rise_04.h"
#include "GameInstance.h"

#include "Spear_Shield_Rise_Down.h"

void CSpear_Shield_Rise_04::Initialize(CKnightGuard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKnightGuard_GamePlay>* CSpear_Shield_Rise_04::Update(CKnightGuard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CSpear_Shield_Rise_Down();
	}

	return nullptr;
}

void CSpear_Shield_Rise_04::Release(CKnightGuard_GamePlay* pActor)
{

}