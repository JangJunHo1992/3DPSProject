#include "stdafx.h"
#include "Varg_Attack1_1.h"
#include "GameInstance.h"

#include "Varg_Attack1_2.h"
#include "Varg_Idle.h"

void CVarg_Attack1_1::Initialize(CVarg_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
	pActor->Set_IsAttack(true);

}

CState<CVarg_GamePlay>* CVarg_Attack1_1::Update(CVarg_GamePlay* pActor, _float fTimeDelta)
{
	_uint iMinimumPlayTime = 15;

	if (pActor->Is_Inputable_Front(iMinimumPlayTime))
	{
		if (CGameInstance::GetInstance()->Mouse_Down(DIM_LB))
		{
			return new CVarg_Attack1_2();
		}
		//pActor->Set_IsAttack(false);
	}

	if (pActor->Is_Animation_End())
	{
		return new CVarg_Idle();
	}

	return nullptr;
}

void CVarg_Attack1_1::Release(CVarg_GamePlay* pActor)
{
	__super::Release(pActor);
	pActor->Set_IsAttack(false);

}

