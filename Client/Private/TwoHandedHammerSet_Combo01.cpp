#include "stdafx.h"
#include "TwoHandedHammerSet_Combo01.h"
#include "GameInstance.h"

#include "TwoHandedHammerSet_Combo02.h"

void CTwoHandedHammerSet_Combo01::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Combo01::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CTwoHandedHammerSet_Combo02();
	}

	return nullptr;
}

void CTwoHandedHammerSet_Combo01::Release(CKing_GamePlay* pActor)
{

}