#include "stdafx.h"
#include "Massive_Greate_Sword_Hit_Front.h"
#include "GameInstance.h"

//#include "GreatDualBlade_Attack_02.h"

void CMassive_Greate_Sword_Hit_Front::Initialize(CDarkKnight_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CDarkKnight_GamePlay>* CMassive_Greate_Sword_Hit_Front::Update(CDarkKnight_GamePlay* pActor, _float fTimeDelta)
{
	//if (pActor->Is_Animation_End())
	//{
	//	return new CGreat_DualBlade_Attack_02();
	//}

	return nullptr;
}

void CMassive_Greate_Sword_Hit_Front::Release(CDarkKnight_GamePlay* pActor)
{

}