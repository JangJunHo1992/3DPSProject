#include "stdafx.h"
#include "GreatDualBlade_Rise_Right_Up.h"
#include "GameInstance.h"

//#include "GreatDualBlade_Attack_01.h"


void CGreatDualBlade_Rise_Right_Up::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Rise_Right_Up::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	//if (pActor->Is_Animation_End()) 
	//{
	//	return new CGreat_DualBlade_Attack_01();
	//}

	return nullptr;
}

void CGreatDualBlade_Rise_Right_Up::Release(CRaider_GamePlay* pActor)
{
	
}