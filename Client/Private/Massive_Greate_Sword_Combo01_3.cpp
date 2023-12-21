#include "stdafx.h"
#include "Massive_Greate_Sword_Combo01_3.h"
#include "GameInstance.h"

//#include "GreatDualBlade_Attack_02.h"

void CMassive_Greate_Sword_Combo01_3::Initialize(CDarkKnight_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CDarkKnight_GamePlay>* CMassive_Greate_Sword_Combo01_3::Update(CDarkKnight_GamePlay* pActor, _float fTimeDelta)
{
	//if (pActor->Is_Animation_End())
	//{
	//	return new CGreat_DualBlade_Attack_02();
	//}

	return nullptr;
}

void CMassive_Greate_Sword_Combo01_3::Release(CDarkKnight_GamePlay* pActor)
{

}