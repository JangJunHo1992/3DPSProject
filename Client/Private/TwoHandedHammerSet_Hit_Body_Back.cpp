#include "stdafx.h"
#include "TwoHandedHammerSet_Hit_Body_Back.h"
#include "GameInstance.h"

//#include "GreatDualBlade_Attack_02.h"

void CTwoHandedHammerSet_Hit_Body_Back::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Hit_Body_Back::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	//if (pActor->Is_Animation_End())
	//{
	//	return new CGreat_DualBlade_Attack_02();
	//}

	return nullptr;
}

void CTwoHandedHammerSet_Hit_Body_Back::Release(CKing_GamePlay* pActor)
{

}