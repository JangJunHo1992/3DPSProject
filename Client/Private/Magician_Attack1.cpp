#include "stdafx.h"
#include "Magician_Attack1.h"
#include "GameInstance.h"


#include "Magician_Idle.h"

void CMagician_Attack1::Initialize(CMagician_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
	//pActor->Set_IsAttack(true);
}

CState<CMagician_GamePlay>* CMagician_Attack1::Update(CMagician_GamePlay* pActor, _float fTimeDelta)
{
	_uint iMinimumPlayTime = 10;
// 
	if (pActor->Is_Inputable_Front(iMinimumPlayTime))
	{
		pActor->Set_IsAttack(true);
	}
	
	if (pActor->Is_Animation_End())
	{
		return new CMagician_Idle();
	}
	if (pActor->Is_Inputable_Back(10))
	{
		pActor->Set_IsAttack(false);
	}

	return nullptr;
}

void CMagician_Attack1::Release(CMagician_GamePlay* pActor)
{
	__super::Release(pActor);
	
}

