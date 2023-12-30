#include "stdafx.h"
#include "Massive_Greate_Sword_Avoid_Right.h"
#include "GameInstance.h"

#include "Massive_Greate_Sword_Buff.h"

void CMassive_Greate_Sword_Avoid_Right::Initialize(CDarkKnight_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CDarkKnight_GamePlay>* CMassive_Greate_Sword_Avoid_Right::Update(CDarkKnight_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CMassive_Greate_Sword_Buff();
	}

	return nullptr;
}

void CMassive_Greate_Sword_Avoid_Right::Release(CDarkKnight_GamePlay* pActor)
{

}