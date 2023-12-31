#include "stdafx.h"
#include "Massive_Greate_Sword_Defense01_Loop.h"
#include "GameInstance.h"

#include "Massive_Greate_Sword_Defense01_End.h"

void CMassive_Greate_Sword_Defense01_Loop::Initialize(CDarkKnight_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CDarkKnight_GamePlay>* CMassive_Greate_Sword_Defense01_Loop::Update(CDarkKnight_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CMassive_Greate_Sword_Defense01_End();
	}

	return nullptr;
}

void CMassive_Greate_Sword_Defense01_Loop::Release(CDarkKnight_GamePlay* pActor)
{

}