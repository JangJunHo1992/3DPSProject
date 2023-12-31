#include "stdafx.h"
#include "Spear_Shield_Roll_Front.h"
#include "GameInstance.h"

#include "Spear_Shield_Roll_Left.h"

void CSpear_Shield_Roll_Front::Initialize(CKnightGuard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKnightGuard_GamePlay>* CSpear_Shield_Roll_Front::Update(CKnightGuard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CSpear_Shield_Roll_Left();
	}

	return nullptr;
}

void CSpear_Shield_Roll_Front::Release(CKnightGuard_GamePlay* pActor)
{

}