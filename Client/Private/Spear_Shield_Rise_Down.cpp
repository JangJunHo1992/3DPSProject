#include "stdafx.h"
#include "Spear_Shield_Rise_Down.h"
#include "GameInstance.h"

#include "Spear_Shield_Roll_Back.h"

void CSpear_Shield_Rise_Down::Initialize(CKnightGuard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKnightGuard_GamePlay>* CSpear_Shield_Rise_Down::Update(CKnightGuard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CSpear_Shield_Roll_Back();
	}

	return nullptr;
}

void CSpear_Shield_Rise_Down::Release(CKnightGuard_GamePlay* pActor)
{

}