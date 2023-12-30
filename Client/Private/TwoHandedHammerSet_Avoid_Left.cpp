#include "stdafx.h"
#include "TwoHandedHammerSet_Avoid_Left.h"
#include "GameInstance.h"

#include "TwoHandedHammerSet_Avoid_Right.h"

void CTwoHandedHammerSet_Avoid_Left::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Avoid_Left::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CTwoHandedHammerSet_Avoid_Right();
	}

	return nullptr;
}

void CTwoHandedHammerSet_Avoid_Left::Release(CKing_GamePlay* pActor)
{

}