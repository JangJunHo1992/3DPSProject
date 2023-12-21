#include "stdafx.h"
#include "TwoHandedHammerSet_Idle_Long.h"
#include "GameInstance.h"

//#include "GreatDualBlade_Attack_02.h"

void CTwoHandedHammerSet_Idle_Long::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Idle_Long::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	//if (pActor->Is_Animation_End())
	//{
	//	return new CGreat_DualBlade_Attack_02();
	//}

	return nullptr;
}

void CTwoHandedHammerSet_Idle_Long::Release(CKing_GamePlay* pActor)
{

}