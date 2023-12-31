#include "stdafx.h"
#include "TwoHandedHammerSet_Dead03.h"
#include "GameInstance.h"

#include "TwoHandedHammerSet_Defense.h"

void CTwoHandedHammerSet_Dead03::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Dead03::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CTwoHandedHammerSet_Defense();
	}

	return nullptr;
}

void CTwoHandedHammerSet_Dead03::Release(CKing_GamePlay* pActor)
{

}