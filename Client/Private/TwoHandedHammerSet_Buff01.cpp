#include "stdafx.h"
#include "TwoHandedHammerSet_Buff01.h"
#include "GameInstance.h"

#include "TwoHandedHammerSet_Combo01.h"

void CTwoHandedHammerSet_Buff01::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Buff01::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CTwoHandedHammerSet_Combo01();
	}

	return nullptr;
}

void CTwoHandedHammerSet_Buff01::Release(CKing_GamePlay* pActor)
{

}