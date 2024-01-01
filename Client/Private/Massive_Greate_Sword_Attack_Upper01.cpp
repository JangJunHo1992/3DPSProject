#include "stdafx.h"
#include "Massive_Greate_Sword_Attack_Upper01.h"
#include "GameInstance.h"

#include "Massive_Greate_Sword_Attack_Upper02.h"

void CMassive_Greate_Sword_Attack_Upper01::Initialize(CDarkKnight_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CDarkKnight_GamePlay>* CMassive_Greate_Sword_Attack_Upper01::Update(CDarkKnight_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CMassive_Greate_Sword_Attack_Upper02();
	}

	return nullptr;
}

void CMassive_Greate_Sword_Attack_Upper01::Release(CDarkKnight_GamePlay* pActor)
{

}