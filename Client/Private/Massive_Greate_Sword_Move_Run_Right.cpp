#include "stdafx.h"
#include "Massive_Greate_Sword_Move_Run_Right.h"
#include "GameInstance.h"

#include "Massive_Greate_Sword_Setmotion01_ATK.h"

void CMassive_Greate_Sword_Move_Run_Right::Initialize(CDarkKnight_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CDarkKnight_GamePlay>* CMassive_Greate_Sword_Move_Run_Right::Update(CDarkKnight_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CMassive_Greate_Sword_Setmotion01_ATK();
	}

	return nullptr;
}

void CMassive_Greate_Sword_Move_Run_Right::Release(CDarkKnight_GamePlay* pActor)
{

}