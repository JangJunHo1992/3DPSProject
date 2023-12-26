#include "stdafx.h"
#include "Giant_Golem_Defence01.h"
#include "GameInstance.h"

//#include "GreatDualBlade_Attack_02.h"

void CGiant_Golem_Defence01::Initialize(CGolem_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CGolem_GamePlay>* CGiant_Golem_Defence01::Update(CGolem_GamePlay* pActor, _float fTimeDelta)
{
	//if (pActor->Is_Animation_End())
	//{
	//	return new CGreat_DualBlade_Attack_02();
	//}

	return nullptr;
}

void CGiant_Golem_Defence01::Release(CGolem_GamePlay* pActor)
{

}