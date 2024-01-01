#include "stdafx.h"
#include "Massive_Greate_Sword_Jump_Falling_Loop.h"
#include "GameInstance.h"

#include "Massive_Greate_Sword_Jump_Landing.h"

void CMassive_Greate_Sword_Jump_Falling_Loop::Initialize(CDarkKnight_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CDarkKnight_GamePlay>* CMassive_Greate_Sword_Jump_Falling_Loop::Update(CDarkKnight_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CMassive_Greate_Sword_Jump_Landing();
	}

	return nullptr;
}

void CMassive_Greate_Sword_Jump_Falling_Loop::Release(CDarkKnight_GamePlay* pActor)
{

}