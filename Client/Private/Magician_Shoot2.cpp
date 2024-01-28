#include "stdafx.h"
#include "Magician_Shoot2.h"
#include "GameInstance.h"


#include "Magician_Idle.h"

void CMagician_Shoot2::Initialize(CMagician_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
	pActor->Set_bCheckShoot(true);
}

CState<CMagician_GamePlay>* CMagician_Shoot2::Update(CMagician_GamePlay* pActor, _float fTimeDelta)
{
	_uint iMinimumPlayTime = 15;
	if (pActor->Is_Inputable_Front(20) && pActor->Get_bCheckShoot() == true)
	{
		pActor->Create_Card();
		pActor->Set_bCheckShoot(false);
	}

	if (pActor->Is_Animation_End())
	{
		return new CMagician_Idle();
	}

	return nullptr;
}

void CMagician_Shoot2::Release(CMagician_GamePlay* pActor)
{
	__super::Release(pActor);
}

