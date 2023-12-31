#include "stdafx.h"
#include "TwoHandedHammerSet_Hit_Body_Front.h"
#include "GameInstance.h"

//#include "TwoHandedHammerSet_Idle.h"
#include "TwoHandedHammerSet_Attack01.h"

void CTwoHandedHammerSet_Hit_Body_Front::Initialize(CKing_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CKing_GamePlay>* CTwoHandedHammerSet_Hit_Body_Front::Update(CKing_GamePlay* pActor, _float fTimeDelta)
{
	//pActor->Knockback(fTimeDelta);
	if (pActor->Is_Animation_End())
	{
		return new CTwoHandedHammerSet_Attack01();
	}

	return nullptr;
}

void CTwoHandedHammerSet_Hit_Body_Front::Release(CKing_GamePlay* pActor)
{

}