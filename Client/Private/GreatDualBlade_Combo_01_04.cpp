#include "stdafx.h"
#include "GreatDualBlade_Combo_01_04.h"
#include "GameInstance.h"

#include "GreatDualBlade_Combo_01_05.h"
#include "GreatDualBlade_Idle.h"


void CGreatDualBlade_Combo_01_04::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true, true, 6);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Combo_01_04::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	_uint iMinimumPlayTime = 12;

	if (pActor->Is_Inputable_Front(iMinimumPlayTime) && CGameInstance::GetInstance()->Key_Down(DIK_Z))
	{
		return new CGreatDualBlade_Combo_01_05();
	}
	if (pActor->Is_Animation_End())
	{
		return new CGreatDualBlade_Idle();
	}

	return nullptr;
}

void CGreatDualBlade_Combo_01_04::Release(CRaider_GamePlay* pActor)
{
	
}