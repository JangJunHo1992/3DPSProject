#include "stdafx.h"
#include "Spear_Shield_Roll_Back.h"
#include "GameInstance.h"

#include "Spear_Shield_Roll_Front.h"

void CSpear_Shield_Roll_Back::Initialize(CKnightGuard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKnightGuard_GamePlay>* CSpear_Shield_Roll_Back::Update(CKnightGuard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CSpear_Shield_Roll_Front();
	}

	return nullptr;
}

void CSpear_Shield_Roll_Back::Release(CKnightGuard_GamePlay* pActor)
{

}