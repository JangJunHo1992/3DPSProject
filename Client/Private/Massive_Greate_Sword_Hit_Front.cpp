#include "stdafx.h"
#include "Massive_Greate_Sword_Hit_Front.h"
#include "GameInstance.h"

//#include "Massive_Greate_Sword_Idle01.h"
#include "Massive_Greate_Sword_Attack_Dash01.h"

void CMassive_Greate_Sword_Hit_Front::Initialize(CDarkKnight_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CDarkKnight_GamePlay>* CMassive_Greate_Sword_Hit_Front::Update(CDarkKnight_GamePlay* pActor, _float fTimeDelta)
{
	//pActor->Knockback(fTimeDelta);
	if (pActor->Is_Animation_End())
	{
		return new CMassive_Greate_Sword_Attack_Dash01();
	}

	return nullptr;
}

void CMassive_Greate_Sword_Hit_Front::Release(CDarkKnight_GamePlay* pActor)
{

}