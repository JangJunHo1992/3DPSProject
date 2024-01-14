#include "stdafx.h"
#include "Player_Dash_Right.h"
#include "GameInstance.h"


void CCovus_Dash_Right::Initialize(CCovus_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true, true);
}

CState<CCovus_GamePlay>* CCovus_Dash_Right::Update(CCovus_GamePlay* pActor, _float fTimeDelta)
{
	pActor->Go_Right(fTimeDelta*0.25);
	if (pActor->Is_Inputable_Back(10))
	{
		return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
	}
	return nullptr;
}

void CCovus_Dash_Right::Release(CCovus_GamePlay* pActor)
{
	__super::Release(pActor);
}