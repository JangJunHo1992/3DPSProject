#include "stdafx.h"
#include "TwoHandedHammerSet_Combo03.h"
#include "GameInstance.h"

#include "TwoHandedHammerSet_Combo04.h"

void CTwoHandedHammerSet_Combo03::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Combo03::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CTwoHandedHammerSet_Combo04();
	}

	return nullptr;
}

void CTwoHandedHammerSet_Combo03::Release(CKing_GamePlay* pActor)
{

}