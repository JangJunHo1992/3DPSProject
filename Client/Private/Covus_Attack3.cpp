#include "stdafx.h"
#include "Covus_Attack3.h"
#include "GameInstance.h"

#include "Covus_Attack4.h"
#include "Player_Idle.h"

void CCovus_Attack3::Initialize(CCovus_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CCovus_GamePlay>* CCovus_Attack3::Update(CCovus_GamePlay* pActor, _float fTimeDelta)
{
	_uint iMinimumPlayTime = 15;

	if (pActor->Is_Inputable_Front(iMinimumPlayTime))
	{
		if (CGameInstance::GetInstance()->Mouse_Down(DIM_LB))
		{
			return new CCovus_Attack4();
		}
		pActor->Set_IsAttack(false);
	}

	if (pActor->Is_Inputable_Back(40))
	{
		return new CCovus_Idle();
	}

	return nullptr;
}

void CCovus_Attack3::Release(CCovus_GamePlay* pActor)
{
	__super::Release(pActor);
}

