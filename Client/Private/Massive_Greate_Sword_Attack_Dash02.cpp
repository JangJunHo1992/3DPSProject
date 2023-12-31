#include "stdafx.h"
#include "Massive_Greate_Sword_Attack_Dash02.h"
#include "GameInstance.h"

#include "Massive_Greate_Sword_Attack_Ground01.h"

void CMassive_Greate_Sword_Attack_Dash02::Initialize(CDarkKnight_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CDarkKnight_GamePlay>* CMassive_Greate_Sword_Attack_Dash02::Update(CDarkKnight_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CMassive_Greate_Sword_Attack_Ground01();
	}

	return nullptr;
}

void CMassive_Greate_Sword_Attack_Dash02::Release(CDarkKnight_GamePlay* pActor)
{

}