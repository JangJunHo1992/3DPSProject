#include "stdafx.h"
#include "Varg_Attack3.h"
#include "GameInstance.h"


#include "Varg_Idle.h"

void CVarg_Attack3::Initialize(CVarg_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
	//pActor->Set_IsAttack(true);

}

CState<CVarg_GamePlay>* CVarg_Attack3::Update(CVarg_GamePlay* pActor, _float fTimeDelta)
{
	_uint iMinimumPlayTime = 15;


	if (pActor->Is_Animation_End())
	{
		return new CVarg_Idle();
	}

	if (pActor->Is_Inputable_Front(20))
	{
		pActor->Set_IsAttack(true);
	}
	if (pActor->Is_Inputable_Back(30))
	{
		pActor->Set_IsAttack(false);
	}
	return nullptr;
}

void CVarg_Attack3::Release(CVarg_GamePlay* pActor)
{
	__super::Release(pActor);
	//pActor->Set_IsAttack(false);

}

