#include "stdafx.h"
#include "TwoHandedHammerSet_Attack07.h"
#include "GameInstance.h"

//#include "GreatDualBlade_Attack_02.h"

void CTwoHandedHammerSet_Attack07::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Attack07::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	//if (pActor->Is_Animation_End())
	//{
	//	return new CGreat_DualBlade_Attack_02();
	//}

	return nullptr;
}

void CTwoHandedHammerSet_Attack07::Release(CKing_GamePlay* pActor)
{

}