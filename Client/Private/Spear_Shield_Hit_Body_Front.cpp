#include "stdafx.h"
#include "Spear_Shield_Hit_Body_Front.h"
#include "GameInstance.h"

#include "Spear_Shield_Attack_01.h"

void CSpear_Shield_Hit_Body_Front::Initialize(CKnightGuard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKnightGuard_GamePlay>* CSpear_Shield_Hit_Body_Front::Update(CKnightGuard_GamePlay* pActor, _float fTimeDelta)
{
	//pActor->Knockback(fTimeDelta);
	if (pActor->Is_Animation_End())
	{
		return new CSpear_Shield_Attack_01();
	}

	return nullptr;
}

void CSpear_Shield_Hit_Body_Front::Release(CKnightGuard_GamePlay* pActor)
{

}