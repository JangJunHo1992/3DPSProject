#include "stdafx.h"
#include "Covus_Parry_R.h"
#include "GameInstance.h"
#include "Covus_Attack1.h"
#include "Covus_Parry_L.h"
#include "Player_Idle.h"

void CCovus_Parry_R::Initialize(CCovus_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CCovus_GamePlay>* CCovus_Parry_R::Update(CCovus_GamePlay* pActor, _float fTimeDelta)
{
	_uint iMinimumPlayTime = 15;

	if (pActor->Is_Inputable_Front(iMinimumPlayTime))
	{
		if (CGameInstance::GetInstance()->Get_DIKeyState(DIK_F))
		{
			return new CCovus_Parry_L();
		}
		pActor->Set_IsAttack(false);
	}
	
	if (CGameInstance::GetInstance()->Get_DIMouseState(DIM_LB))
	{
		return new CCovus_Attack1();
	}
	
	if (pActor->Is_Inputable_Back(40))
	{
		return new CCovus_Idle();
	}

	return nullptr;
}

void CCovus_Parry_R::Release(CCovus_GamePlay* pActor)
{
	__super::Release(pActor);
	pActor->Set_IsAttack(false);

}

