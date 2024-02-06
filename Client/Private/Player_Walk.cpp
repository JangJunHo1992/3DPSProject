#include "Player_Walk.h"
#include "GameInstance.h"


void CCovus_Walk::Initialize(CCovus_GamePlay* pActor)
{
	__super::Initialize(pActor);
	
}

void CCovus_Walk::Release(CCovus_GamePlay* pActor)
{
	__super::Release(pActor);
	m_pGameInstance->Stop_Sound(SOUND_MonsterFootStep);
}

CState<CCovus_GamePlay>* CCovus_Walk::Update_State(CCovus_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	--m_iFootStepCheck;

	if (m_iFootStepCheck == 13)
	{
		_uint iRandom = rand() % 10;
		switch (iRandom)
		{
		case 0:
			m_pGameInstance->Play_Sound(L"PLAYER_FOOTSTEP", L"Fantasy_Game_Footstep_Dirt_Medium_A.ogg", SOUND_PLAYERFootStep, 1.f);
			break;
		case 1:
			m_pGameInstance->Play_Sound(L"PLAYER_FOOTSTEP", L"Fantasy_Game_Footstep_Dirt_Medium_B.ogg", SOUND_PLAYERFootStep, 1.f);
			break;
		case 2:
			m_pGameInstance->Play_Sound(L"PLAYER_FOOTSTEP", L"Fantasy_Game_Footstep_Dirt_Medium_C.ogg", SOUND_PLAYERFootStep, 1.f);
			break;
		case 3:
			m_pGameInstance->Play_Sound(L"PLAYER_FOOTSTEP", L"Fantasy_Game_Footstep_Dirt_Medium_D.ogg", SOUND_PLAYERFootStep, 1.f);
			break;
		case 4:
			m_pGameInstance->Play_Sound(L"PLAYER_FOOTSTEP", L"Fantasy_Game_Footstep_Dirt_Medium_E.ogg", SOUND_PLAYERFootStep, 1.f);
			break;
		case 5:
			m_pGameInstance->Play_Sound(L"PLAYER_FOOTSTEP", L"Fantasy_Game_Footstep_Dirt_Medium_F.ogg", SOUND_PLAYERFootStep, 1.f);
			break;
		case 6:
			m_pGameInstance->Play_Sound(L"PLAYER_FOOTSTEP", L"Fantasy_Game_Footstep_Dirt_Medium_G.ogg", SOUND_PLAYERFootStep, 1.f);
			break;
		case 7:
			m_pGameInstance->Play_Sound(L"PLAYER_FOOTSTEP", L"Fantasy_Game_Footstep_Dirt_Medium_H.ogg", SOUND_PLAYERFootStep, 1.f);
			break;
		case 8:
			m_pGameInstance->Play_Sound(L"PLAYER_FOOTSTEP", L"Fantasy_Game_Footstep_Dirt_Medium_I.ogg", SOUND_PLAYERFootStep, 1.f);
			break;
		case 9:
			m_pGameInstance->Play_Sound(L"PLAYER_FOOTSTEP", L"Fantasy_Game_Footstep_Dirt_Medium_J.ogg", SOUND_PLAYERFootStep, 1.f);
			break;
		}
	}

	
	if (m_iFootStepCheck < 0)
		m_iFootStepCheck = 25;
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
