#include "stdafx.h"
#include "GreatDualBlade_Combo_01_01.h"
#include "GameInstance.h"

#include "GreatDualBlade_Combo_01_02.h"
#include "GreatDualBlade_Idle.h"

void CGreatDualBlade_Combo_01_01::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Combo_01_01::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	_uint iMinimumPlayTime = 15;

	if (pActor->Is_Inputable_Front(iMinimumPlayTime) && CGameInstance::GetInstance()->Key_Down(DIK_Z))
	{
		return new CGreatDualBlade_Combo_01_02();
	}
	if (pActor->Is_Animation_End())
	{
		return new CGreatDualBlade_Idle();
	}

	return nullptr;
}

void CGreatDualBlade_Combo_01_01::Release(CRaider_GamePlay* pActor)
{
	
}