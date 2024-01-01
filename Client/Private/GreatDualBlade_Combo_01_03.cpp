#include "stdafx.h"
#include "GreatDualBlade_Combo_01_03.h"
#include "GameInstance.h"

#include "GreatDualBlade_Combo_01_04.h"
#include "GreatDualBlade_Idle.h"


void CGreatDualBlade_Combo_01_03::Initialize(CRaider_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true, true, 9);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Combo_01_03::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	_uint iMinimumPlayTime = 24;

	if (pActor->Is_Inputable_Front(iMinimumPlayTime))
	{
		if (CGameInstance::GetInstance()->Key_Down(DIK_Z))
		{
			return new CGreatDualBlade_Combo_01_04();
		}
		pActor->Set_IsAttack(false);
	}

	if (pActor->Is_Animation_End())
	{
		return new CGreatDualBlade_Idle();
	}

	return nullptr;
}

void CGreatDualBlade_Combo_01_03::Release(CRaider_GamePlay* pActor)
{
	__super::Release(pActor);
}