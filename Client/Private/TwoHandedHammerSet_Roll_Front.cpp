#include "stdafx.h"
#include "TwoHandedHammerSet_Roll_Front.h"
#include "GameInstance.h"

#include "TwoHandedHammerSet_Idle.h"

void CTwoHandedHammerSet_Roll_Front::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Roll_Front::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CTwoHandedHammerSet_Idle();
	}

	return nullptr;
}

void CTwoHandedHammerSet_Roll_Front::Release(CKing_GamePlay* pActor)
{

}