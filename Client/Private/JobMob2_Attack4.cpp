#include "stdafx.h"
#include "JobMob2_Attack4.h"
#include "GameInstance.h"


#include "JobMob2_Idle.h"

void CJobMob2_Attack4::Initialize(CJobMob2_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
	pActor->Set_IsAttack(true);

}

CState<CJobMob2_GamePlay>* CJobMob2_Attack4::Update(CJobMob2_GamePlay* pActor, _float fTimeDelta)
{
	_uint iMinimumPlayTime = 15;


	if (pActor->Is_Animation_End())
	{
		return new CJobMob2_Idle();
	}

	return nullptr;
}

void CJobMob2_Attack4::Release(CJobMob2_GamePlay* pActor)
{
	__super::Release(pActor);
	pActor->Set_IsAttack(false);

}

