#include "stdafx.h"
#include "TwoHandedHammerSet_Knockdown02.h"
#include "GameInstance.h"

#include "TwoHandedHammerSet_Rise01.h"
#include "TwoHandedHammerSet_Idle.h"

void CTwoHandedHammerSet_Knockdown02::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Knockdown02::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CTwoHandedHammerSet_Rise01();
		//return new CTwoHandedHammerSet_Idle();
	}

	return nullptr;
}

void CTwoHandedHammerSet_Knockdown02::Release(CKing_GamePlay* pActor)
{

}