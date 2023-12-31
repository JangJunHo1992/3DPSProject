#include "stdafx.h"
#include "Massive_Greate_Sword_Attack_Sting.h"
#include "GameInstance.h"

#include "Massive_Greate_Sword_Attack_Upper01.h"

void CMassive_Greate_Sword_Attack_Sting::Initialize(CDarkKnight_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CDarkKnight_GamePlay>* CMassive_Greate_Sword_Attack_Sting::Update(CDarkKnight_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CMassive_Greate_Sword_Attack_Upper01();
	}

	return nullptr;
}

void CMassive_Greate_Sword_Attack_Sting::Release(CDarkKnight_GamePlay* pActor)
{

}