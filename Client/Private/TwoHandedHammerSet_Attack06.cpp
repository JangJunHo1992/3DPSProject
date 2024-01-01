#include "stdafx.h"
#include "TwoHandedHammerSet_Attack06.h"
#include "GameInstance.h"

#include "TwoHandedHammerSet_Attack07.h"

void CTwoHandedHammerSet_Attack06::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Attack06::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CTwoHandedHammerSet_Attack07();
	}

	return nullptr;
}

void CTwoHandedHammerSet_Attack06::Release(CKing_GamePlay* pActor)
{

}