#include "stdafx.h"
#include "TwoHandedHammerSet_Down.h"
#include "GameInstance.h"

#include "TwoHandedHammerSet_Jump.h"

void CTwoHandedHammerSet_Down::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Down::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CTwoHandedHammerSet_Jump();
	}

	return nullptr;
}

void CTwoHandedHammerSet_Down::Release(CKing_GamePlay* pActor)
{

}