#include "stdafx.h"
#include "Covus_Parry_L.h"
#include "GameInstance.h"

#include "Covus_Parry_R.h"
#include "Player_Idle.h"

void CCovus_Parry_L::Initialize(CCovus_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CCovus_GamePlay>* CCovus_Parry_L::Update(CCovus_GamePlay* pActor, _float fTimeDelta)
{
	_uint iMinimumPlayTime = 15;

	if (pActor->Is_Inputable_Front(iMinimumPlayTime))
	{
		if (CGameInstance::GetInstance()->Get_DIKeyState(DIK_F))
		{
			return new CCovus_Parry_R();
		}
		pActor->Set_IsAttack(false);
	}

	if (pActor->Is_Animation_End())
	{
		return new CCovus_Idle();
	}

	return nullptr;
}

void CCovus_Parry_L::Release(CCovus_GamePlay* pActor)
{
	__super::Release(pActor);
}

