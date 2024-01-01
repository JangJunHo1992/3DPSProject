#include "stdafx.h"
#include "Spear_Shield_Dash_Sting.h"
#include "GameInstance.h"

#include "Spear_Shield_Defence_Mode_Start.h"

void CSpear_Shield_Dash_Sting::Initialize(CKnightGuard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKnightGuard_GamePlay>* CSpear_Shield_Dash_Sting::Update(CKnightGuard_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CSpear_Shield_Defence_Mode_Start();
	}

	return nullptr;
}

void CSpear_Shield_Dash_Sting::Release(CKnightGuard_GamePlay* pActor)
{

}