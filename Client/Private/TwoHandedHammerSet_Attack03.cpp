#include "stdafx.h"
#include "TwoHandedHammerSet_Attack03.h"
#include "GameInstance.h"

#include "TwoHandedHammerSet_Attack04.h"

void CTwoHandedHammerSet_Attack03::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Attack03::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CTwoHandedHammerSet_Attack04();
	}

	return nullptr;
}

void CTwoHandedHammerSet_Attack03::Release(CKing_GamePlay* pActor)
{

}