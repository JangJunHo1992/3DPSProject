#include "stdafx.h"
#include "Covus_Attack5.h"
#include "GameInstance.h"
#include "Covus_Parry_L.h"
#include "Player_Idle.h"

void CCovus_Attack5::Initialize(CCovus_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true, true, 3);
	

}

CState<CCovus_GamePlay>* CCovus_Attack5::Update(CCovus_GamePlay* pActor, _float fTimeDelta)
{
	_uint iMinimumPlayTime = 15;
	if (pActor->Is_Inputable_Front(10))
	{
		pActor->Set_IsAttack(true);
	}
	if (pActor->Is_Inputable_Front(40))
	{
		return new CCovus_Idle();
	}

	if (pActor->Is_Inputable_Front(iMinimumPlayTime))
	{
		if (CGameInstance::GetInstance()->Get_DIKeyState(DIK_F))
		{
			return new CCovus_Parry_L();
			pActor->Set_IsAttack(false);
		}
	}
// 	if (pActor->Is_Inputable_Back(45))
// 	{
// 		return new CCovus_Idle();
// 	}
	if (pActor->Is_Inputable_Front(30))
	{
		//pActor->Set_IsAttack(false);
	}
	return nullptr;
}

void CCovus_Attack5::Release(CCovus_GamePlay* pActor)
{
	__super::Release(pActor);
	pActor->Set_IsAttack(false);

}

