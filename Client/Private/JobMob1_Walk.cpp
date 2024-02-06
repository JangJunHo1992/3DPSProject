#include "JobMob1_Walk.h"
#include "GameInstance.h"


void CJobMob1_Walk::Initialize(CJobMob1_GamePlay* pActor)
{
	__super::Initialize(pActor);
}

void CJobMob1_Walk::Release(CJobMob1_GamePlay* pActor)
{
	__super::Release(pActor);
	m_pGameInstance->Stop_Sound(SOUND_MonsterFootStep);
}

CState<CJobMob1_GamePlay>* CJobMob1_Walk::Update_State(CJobMob1_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	--m_iFootStepCheck;

	if (m_iFootStepCheck == 13)
	{
		_uint iRandom = rand() % 4;
		switch (iRandom)
		{
		case 0:
			m_pGameInstance->Play_Sound(L"ENEMY_FOOTSTEP", L"FootStep_Gardener_01.ogg", SOUND_MonsterFootStep, 1.f);
			break;
		case 1:
			m_pGameInstance->Play_Sound(L"ENEMY_FOOTSTEP", L"FootStep_Gardener_02.ogg", SOUND_MonsterFootStep, 1.f);
			break;
		case 2:
			m_pGameInstance->Play_Sound(L"ENEMY_FOOTSTEP", L"FootStep_Gardener_03.ogg", SOUND_MonsterFootStep, 1.f);
			break;
		case 3:
			m_pGameInstance->Play_Sound(L"ENEMY_FOOTSTEP", L"FootStep_Gardener_04.ogg", SOUND_MonsterFootStep, 1.f);
			break;
		}
	}


	if (m_iFootStepCheck < 0)
		m_iFootStepCheck = 25;
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
