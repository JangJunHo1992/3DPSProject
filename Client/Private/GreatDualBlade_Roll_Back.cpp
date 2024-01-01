#include "stdafx.h"
#include "GreatDualBlade_Roll_Back.h"


void CGreatDualBlade_Roll_Back::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Roll_Back::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	return Update_State(pActor, fTimeDelta, g_iAnimIndex);
}

void CGreatDualBlade_Roll_Back::Release(CRaider_GamePlay* pActor)
{
	
}