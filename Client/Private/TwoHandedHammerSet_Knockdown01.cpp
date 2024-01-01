#include "stdafx.h"
#include "TwoHandedHammerSet_Knockdown01.h"
#include "GameInstance.h"

#include "TwoHandedHammerSet_Rise01.h"

void CTwoHandedHammerSet_Knockdown01::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, false);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Knockdown01::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CTwoHandedHammerSet_Rise01();
	}

	return nullptr;
}

void CTwoHandedHammerSet_Knockdown01::Release(CKing_GamePlay* pActor)
{

}