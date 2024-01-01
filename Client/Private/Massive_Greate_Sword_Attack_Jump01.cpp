#include "stdafx.h"
#include "Massive_Greate_Sword_Attack_Jump01.h"
#include "GameInstance.h"

#include "Massive_Greate_Sword_Attack_Jump02.h"

void CMassive_Greate_Sword_Attack_Jump01::Initialize(CDarkKnight_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CDarkKnight_GamePlay>* CMassive_Greate_Sword_Attack_Jump01::Update(CDarkKnight_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CMassive_Greate_Sword_Attack_Jump02();
	}

	return nullptr;
}

void CMassive_Greate_Sword_Attack_Jump01::Release(CDarkKnight_GamePlay* pActor)
{

}