#include "stdafx.h"
#include "TwoHandedHammerSet_Attack_1H_Around2.h"
#include "GameInstance.h"

#include "TwoHandedHammerSet_Attack02.h"

void CTwoHandedHammerSet_Attack_1H_Around2::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Attack_1H_Around2::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CTwoHandedHammerSet_Attack02();
	}

	return nullptr;
}

void CTwoHandedHammerSet_Attack_1H_Around2::Release(CKing_GamePlay* pActor)
{

}