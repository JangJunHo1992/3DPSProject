#include "stdafx.h"
#include "TwoHandedHammerSet_Attack02.h"
#include "GameInstance.h"

#include "TwoHandedHammerSet_Attack03.h"

void CTwoHandedHammerSet_Attack02::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Attack02::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CTwoHandedHammerSet_Attack03();
	}

	return nullptr;
}

void CTwoHandedHammerSet_Attack02::Release(CKing_GamePlay* pActor)
{

}