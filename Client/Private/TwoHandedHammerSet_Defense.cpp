#include "stdafx.h"
#include "TwoHandedHammerSet_Defense.h"
#include "GameInstance.h"

#include "TwoHandedHammerSet_Down.h"

void CTwoHandedHammerSet_Defense::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Defense::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CTwoHandedHammerSet_Down();
	}

	return nullptr;
}

void CTwoHandedHammerSet_Defense::Release(CKing_GamePlay* pActor)
{

}