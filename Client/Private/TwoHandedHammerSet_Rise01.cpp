#include "stdafx.h"
#include "TwoHandedHammerSet_Rise01.h"
#include "GameInstance.h"

#include "TwoHandedHammerSet_Roll_Front.h"

void CTwoHandedHammerSet_Rise01::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Rise01::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CTwoHandedHammerSet_Roll_Front();
	}

	return nullptr;
}

void CTwoHandedHammerSet_Rise01::Release(CKing_GamePlay* pActor)
{

}