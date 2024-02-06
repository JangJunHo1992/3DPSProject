#include "stdafx.h"
#include "Varg_Attack2_1.h"
#include "GameInstance.h"

#include "Varg_Attack2_2.h"
#include "Varg_Idle.h"

void CVarg_Attack2_1::Initialize(CVarg_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
	//pActor->Set_IsAttack(true);
	m_pGameInstance->Play_Sound(L"VARG", L"CV_Varg_AtkAction04.ogg", SOUND_EFFECT, 1.f);
	m_pGameInstance->Play_Sound(L"VARG", L"Urd_Attack06.ogg", SOUND_EFFECT2, 1.f);
}

CState<CVarg_GamePlay>* CVarg_Attack2_1::Update(CVarg_GamePlay* pActor, _float fTimeDelta)
{
	_uint iMinimumPlayTime = 15;

	if (pActor->Is_Inputable_Front(iMinimumPlayTime))
	{
		if (CGameInstance::GetInstance()->Mouse_Down(DIM_LB))
		{
			return new CVarg_Attack2_2();
		}
		//pActor->Set_IsAttack(false);
	}
	if (pActor->Is_Inputable_Front(20))
	{
		pActor->Set_IsAttack(true);
	}
	if (pActor->Is_Inputable_Back(30))
	{
		pActor->Set_IsAttack(false);
	}
	if (pActor->Is_Animation_End())
	{
		return new CVarg_Idle();
	}

	return nullptr;
}

void CVarg_Attack2_1::Release(CVarg_GamePlay* pActor)
{
	__super::Release(pActor);
	//pActor->Set_IsAttack(false);

}

