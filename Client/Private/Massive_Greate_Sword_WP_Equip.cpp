#include "stdafx.h"
#include "Massive_Greate_Sword_WP_Equip.h"
#include "GameInstance.h"

#include "Massive_Greate_Sword_WP_Unequip.h"

void CMassive_Greate_Sword_WP_Equip::Initialize(CDarkKnight_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CDarkKnight_GamePlay>* CMassive_Greate_Sword_WP_Equip::Update(CDarkKnight_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CMassive_Greate_Sword_WP_Unequip();
	}

	return nullptr;
}

void CMassive_Greate_Sword_WP_Equip::Release(CDarkKnight_GamePlay* pActor)
{

}