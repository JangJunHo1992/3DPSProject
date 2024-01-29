#include "stdafx.h"
#include "Magician_Start.h"
#include "GameInstance.h"
#include "Magician_Idle.h"



void CMagician_Start::Initialize(CMagician_GamePlay* pActor)
{
	__super::Initialize(pActor);

	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CMagician_GamePlay>* CMagician_Start::Update(CMagician_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		pActor->Set_StartScene2(false);
		return new CMagician_Idle();
	}
}

void CMagician_Start::Release(CMagician_GamePlay* pActor)
{
	__super::Release(pActor);
}