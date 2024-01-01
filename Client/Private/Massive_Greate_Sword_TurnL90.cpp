#include "stdafx.h"
#include "Massive_Greate_Sword_TurnL90.h"
#include "GameInstance.h"

#include "Massive_Greate_Sword_TurnL180.h"

void CMassive_Greate_Sword_TurnL90::Initialize(CDarkKnight_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CDarkKnight_GamePlay>* CMassive_Greate_Sword_TurnL90::Update(CDarkKnight_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CMassive_Greate_Sword_TurnL180();
	}

	return nullptr;
}

void CMassive_Greate_Sword_TurnL90::Release(CDarkKnight_GamePlay* pActor)
{

}