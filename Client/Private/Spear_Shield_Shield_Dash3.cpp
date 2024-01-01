#include "stdafx.h"
#include "Spear_Shield_Shield_Dash3.h"
#include "GameInstance.h"

#include "Spear_Shield_Dash_Sting.h"

void CSpear_Shield_Shield_Dash3::Initialize(CKnightGuard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKnightGuard_GamePlay>* CSpear_Shield_Shield_Dash3::Update(CKnightGuard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CSpear_Shield_Dash_Sting();
	}

	return nullptr;
}

void CSpear_Shield_Shield_Dash3::Release(CKnightGuard_GamePlay* pActor)
{

}