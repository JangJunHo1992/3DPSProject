#include "stdafx.h"
#include "Varg_Walk_Front.h"
#include "GameInstance.h"



void CVarg_Walk_Front::Initialize(CVarg_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true, false);
}

CState<CVarg_GamePlay>* CVarg_Walk_Front::Update(CVarg_GamePlay* pActor, _float fTimeDelta)
{
	pActor->Go_Straight(fTimeDelta * 0.5);

	return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
}

void CVarg_Walk_Front::Release(CVarg_GamePlay* pActor)
{
	__super::Release(pActor);
}