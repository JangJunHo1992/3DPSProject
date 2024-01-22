#include "stdafx.h"
#include "Covus_Attack5.h"
#include "GameInstance.h"

#include "Player_Idle.h"

void CCovus_Attack5::Initialize(CCovus_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true, true, 3);
}

CState<CCovus_GamePlay>* CCovus_Attack5::Update(CCovus_GamePlay* pActor, _float fTimeDelta)
{
	_uint iMinimumPlayTime = 25;

	if (pActor->Is_Inputable_Front(iMinimumPlayTime))
	{
		pActor->Set_IsAttack(false);
	}

	if (pActor->Is_Inputable_Back(40))
	{
		return new CCovus_Idle();
	}

	return nullptr;
}

void CCovus_Attack5::Release(CCovus_GamePlay* pActor)
{
	__super::Release(pActor);
}

