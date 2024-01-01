#include "stdafx.h"
#include "Massive_Greate_Sword_TurnR180.h"
#include "GameInstance.h"

#include "Massive_Greate_Sword_Idle01.h"

void CMassive_Greate_Sword_TurnR180::Initialize(CDarkKnight_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CDarkKnight_GamePlay>* CMassive_Greate_Sword_TurnR180::Update(CDarkKnight_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CMassive_Greate_Sword_Idle01();
	}

	return nullptr;
}

void CMassive_Greate_Sword_TurnR180::Release(CDarkKnight_GamePlay* pActor)
{

}