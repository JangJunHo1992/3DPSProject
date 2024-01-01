#include "stdafx.h"
#include "Massive_Greate_Sword_Avoid_Left.h"
#include "GameInstance.h"

#include "Massive_Greate_Sword_Avoid_Right.h"

void CMassive_Greate_Sword_Avoid_Left::Initialize(CDarkKnight_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CDarkKnight_GamePlay>* CMassive_Greate_Sword_Avoid_Left::Update(CDarkKnight_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CMassive_Greate_Sword_Avoid_Right();
	}

	return nullptr;
}

void CMassive_Greate_Sword_Avoid_Left::Release(CDarkKnight_GamePlay* pActor)
{

}