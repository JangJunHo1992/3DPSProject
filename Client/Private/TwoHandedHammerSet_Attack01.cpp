#include "stdafx.h"
#include "TwoHandedHammerSet_Attack01.h"
#include "GameInstance.h"

#include "TwoHandedHammerSet_Attack_1H_Around.h"

void CTwoHandedHammerSet_Attack01::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Attack01::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CTwoHandedHammerSet_Attack_1H_Around();
	}

	return nullptr;
}

void CTwoHandedHammerSet_Attack01::Release(CKing_GamePlay* pActor)
{

}