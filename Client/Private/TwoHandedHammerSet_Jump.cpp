#include "stdafx.h"
#include "TwoHandedHammerSet_Jump.h"
#include "GameInstance.h"

#include "TwoHandedHammerSet_Rise01.h"

void CTwoHandedHammerSet_Jump::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Jump::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CTwoHandedHammerSet_Rise01();
	}

	return nullptr;
}

void CTwoHandedHammerSet_Jump::Release(CKing_GamePlay* pActor)
{

}