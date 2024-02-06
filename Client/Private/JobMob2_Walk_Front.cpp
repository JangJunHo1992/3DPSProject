#include "stdafx.h"
#include "JobMob2_Walk_Front.h"
#include "GameInstance.h"



void CJobMob2_Walk_Front::Initialize(CJobMob2_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true, false);
}

CState<CJobMob2_GamePlay>* CJobMob2_Walk_Front::Update(CJobMob2_GamePlay* pActor, _float fTimeDelta)
{
	pActor->Go_Straight(fTimeDelta * 0.5);
	--m_iFootStepCheck;

	if (m_iFootStepCheck == 13)
	{
		_uint iRandom = rand() % 6;
		switch (iRandom)
		{
		case 0:
			m_pGameInstance->Play_Sound(L"ENEMY_FOOTSTEP", L"FootStep_VillagerF_01.ogg", SOUND_MonsterFootStep, 1.f);
			break;
		case 1:
			m_pGameInstance->Play_Sound(L"ENEMY_FOOTSTEP", L"FootStep_VillagerF_02.ogg", SOUND_MonsterFootStep, 1.f);
			break;
		case 2:
			m_pGameInstance->Play_Sound(L"ENEMY_FOOTSTEP", L"FootStep_VillagerF_03.ogg", SOUND_MonsterFootStep, 1.f);
			break;
		case 3:
			m_pGameInstance->Play_Sound(L"ENEMY_FOOTSTEP", L"FootStep_VillagerF_04.ogg", SOUND_MonsterFootStep, 1.f);
			break;
		case 4:
			m_pGameInstance->Play_Sound(L"ENEMY_FOOTSTEP", L"FootStep_VillagerF_05.ogg", SOUND_MonsterFootStep, 1.f);
			break;
		case 5:
			m_pGameInstance->Play_Sound(L"ENEMY_FOOTSTEP", L"FootStep_VillagerF_06.ogg", SOUND_MonsterFootStep, 1.f);
			break;
		}
	}


	if (m_iFootStepCheck < 0)
		m_iFootStepCheck = 25;
	return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
}

void CJobMob2_Walk_Front::Release(CJobMob2_GamePlay* pActor)
{
	__super::Release(pActor);
	
}