#include "stdafx.h"
#include "Massive_Greate_Sword_Avoid_Front.h"
#include "GameInstance.h"

#include "Massive_Greate_Sword_Avoid_Left.h"

void CMassive_Greate_Sword_Avoid_Front::Initialize(CDarkKnight_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CDarkKnight_GamePlay>* CMassive_Greate_Sword_Avoid_Front::Update(CDarkKnight_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CMassive_Greate_Sword_Avoid_Left();
	}

	return nullptr;
}

void CMassive_Greate_Sword_Avoid_Front::Release(CDarkKnight_GamePlay* pActor)
{

}