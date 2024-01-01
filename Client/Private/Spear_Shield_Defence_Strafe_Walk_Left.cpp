#include "stdafx.h"
#include "Spear_Shield_Defence_Strafe_Walk_Left.h"
#include "GameInstance.h"

//#include "GreatDualBlade_Attack_02.h"

void CSpear_Shield_Defence_Strafe_Walk_Left::Initialize(CKnightGuard_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKnightGuard_GamePlay>* CSpear_Shield_Defence_Strafe_Walk_Left::Update(CKnightGuard_GamePlay* pActor, _float fTimeDelta)
{
	//if (pActor->Is_Animation_End())
	//{
	//	return new CGreat_DualBlade_Attack_02();
	//}

	return nullptr;
}

void CSpear_Shield_Defence_Strafe_Walk_Left::Release(CKnightGuard_GamePlay* pActor)
{

}