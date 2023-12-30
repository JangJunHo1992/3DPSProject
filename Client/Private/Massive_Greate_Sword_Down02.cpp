#include "stdafx.h"
#include "Massive_Greate_Sword_Down02.h"
#include "GameInstance.h"

#include "Massive_Greate_Sword_WP_Equip.h"

void CMassive_Greate_Sword_Down02::Initialize(CDarkKnight_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CDarkKnight_GamePlay>* CMassive_Greate_Sword_Down02::Update(CDarkKnight_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CMassive_Greate_Sword_WP_Equip();
	}

	return nullptr;
}

void CMassive_Greate_Sword_Down02::Release(CDarkKnight_GamePlay* pActor)
{

}