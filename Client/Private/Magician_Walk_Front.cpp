#include "stdafx.h"
#include "Magician_Walk_Front.h"
#include "GameInstance.h"



void CMagician_Walk_Front::Initialize(CMagician_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true, false);
}

CState<CMagician_GamePlay>* CMagician_Walk_Front::Update(CMagician_GamePlay* pActor, _float fTimeDelta)
{
	pActor->Go_Straight(fTimeDelta * 0.5);

	return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
}

void CMagician_Walk_Front::Release(CMagician_GamePlay* pActor)
{
	__super::Release(pActor);
}