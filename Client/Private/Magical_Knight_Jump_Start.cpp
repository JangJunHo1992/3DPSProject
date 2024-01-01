#include "stdafx.h"
#include "Magical_Knight_Jump_Start.h"
#include "GameInstance.h"

//#include "GreatDualBlade_Attack_02.h"

void CMagical_Knight_Jump_Start::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CMagical_Knight_Jump_Start::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	//if (pActor->Is_Animation_End())
	//{
	//	return new CGreat_DualBlade_Attack_02();
	//}

	return nullptr;
}

void CMagical_Knight_Jump_Start::Release(CRaider_GamePlay* pActor)
{

}