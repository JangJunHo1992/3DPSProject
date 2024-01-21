#include "stdafx.h"
#include "JobMob1_Dead.h"
#include "GameInstance.h"
#include "JobMob1_Idle.h"

void CJobMob1_Dead::Initialize(CJobMob1_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CJobMob1_GamePlay>* CJobMob1_Dead::Update(CJobMob1_GamePlay* pActor, _float fTimeDelta)
{
// 	if (pActor->Is_Animation_End() && m_pGameInstance->Get_DIKeyState(DIK_SPACE))
// 	{
// 		return new CJobMob1_Idle();
// 	}

	return nullptr;
}

void CJobMob1_Dead::Release(CJobMob1_GamePlay* pActor)
{
}
