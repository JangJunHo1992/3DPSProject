#include "stdafx.h"
#include "Varg_StartDemo.h"
#include "GameInstance.h"
#include "Varg_Idle.h"



void CVarg_StartDemo::Initialize(CVarg_GamePlay* pActor)
{
	__super::Initialize(pActor);

	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CVarg_GamePlay>* CVarg_StartDemo::Update(CVarg_GamePlay* pActor, _float fTimeDelta)
{

	if (pActor->Is_Animation_End())
	{
		pActor->Set_StartScene(false);
		return new CVarg_Idle();

	}


	return nullptr;

}

void CVarg_StartDemo::Release(CVarg_GamePlay* pActor)
{
	__super::Release(pActor);
}