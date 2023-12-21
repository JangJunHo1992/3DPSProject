#include "stdafx.h"
#include "Magical_Knight_Combo02_3.h"
#include "GameInstance.h"

//#include "GreatDualBlade_Attack_02.h"

void CMagical_Knight_Combo02_3::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CMagical_Knight_Combo02_3::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	//if (pActor->Is_Animation_End())
	//{
	//	return new CGreat_DualBlade_Attack_02();
	//}

	return nullptr;
}

void CMagical_Knight_Combo02_3::Release(CRaider_GamePlay* pActor)
{

}