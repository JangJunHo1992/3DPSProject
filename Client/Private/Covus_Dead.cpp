#include "stdafx.h"
#include "Covus_Dead.h"
#include "GameInstance.h"
#include "Player_Idle.h"

void CCovus_Dead::Initialize(CCovus_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CCovus_GamePlay>* CCovus_Dead::Update(CCovus_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End()&&m_pGameInstance->Get_DIKeyState(DIK_SPACE))
	{
		return new CCovus_Idle();
	}

	return nullptr;
}

void CCovus_Dead::Release(CCovus_GamePlay* pActor)
{
}
