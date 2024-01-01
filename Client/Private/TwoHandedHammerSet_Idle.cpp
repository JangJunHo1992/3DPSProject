#include "stdafx.h"
#include "TwoHandedHammerSet_Idle.h"
#include "GameInstance.h"

#include "TwoHandedHammerSet_Knockdown02.h"
#include "TwoHandedHammerSet_Hit_Body_Front.h"


void CTwoHandedHammerSet_Idle::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Idle::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	//if (pActor->Is_Animation_End())
	//{
	//	return new CTwoHandedHammerSet_Knockdown02();
	//}

	return nullptr;
}

void CTwoHandedHammerSet_Idle::Release(CKing_GamePlay* pActor)
{

}