#include "stdafx.h"
#include "Massive_Greate_Sword_Combo02_3.h"
#include "GameInstance.h"

#include "Massive_Greate_Sword_Combo03_1.h"

void CMassive_Greate_Sword_Combo02_3::Initialize(CDarkKnight_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CDarkKnight_GamePlay>* CMassive_Greate_Sword_Combo02_3::Update(CDarkKnight_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		return new CMassive_Greate_Sword_Combo03_1();
	}

	return nullptr;
}

void CMassive_Greate_Sword_Combo02_3::Release(CDarkKnight_GamePlay* pActor)
{

}