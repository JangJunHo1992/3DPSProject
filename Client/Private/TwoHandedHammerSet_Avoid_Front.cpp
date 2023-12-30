#include "stdafx.h"
#include "TwoHandedHammerSet_Avoid_Front.h"
#include "GameInstance.h"

#include "TwoHandedHammerSet_Avoid_Left.h"

void CTwoHandedHammerSet_Avoid_Front::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Avoid_Front::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CTwoHandedHammerSet_Avoid_Left();
	}

	return nullptr;
}

void CTwoHandedHammerSet_Avoid_Front::Release(CKing_GamePlay* pActor)
{

}