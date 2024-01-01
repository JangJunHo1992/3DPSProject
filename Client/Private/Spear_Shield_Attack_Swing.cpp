#include "stdafx.h"
#include "Spear_Shield_Attack_Swing.h"
#include "GameInstance.h"

#include "Spear_Shield_Combo_Stings_01.h"

void CSpear_Shield_Attack_Swing::Initialize(CKnightGuard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKnightGuard_GamePlay>* CSpear_Shield_Attack_Swing::Update(CKnightGuard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CSpear_Shield_Combo_Stings_01();
	}

	return nullptr;
}

void CSpear_Shield_Attack_Swing::Release(CKnightGuard_GamePlay* pActor)
{

}