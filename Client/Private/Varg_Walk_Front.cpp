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
	--m_iFootStepCheck;

	if (m_iFootStepCheck == 5)
	{
		_uint iRandom = rand() % 4;
		switch (iRandom)
		{
		case 0:
			m_pGameInstance->Play_Sound(L"VARG", L"FootStep_FullPlateA_01.ogg", SOUND_MonsterFootStep, 1.f);
			break;
		case 1:
			m_pGameInstance->Play_Sound(L"VARG", L"FootStep_FullPlateA_02.ogg", SOUND_MonsterFootStep, 1.f);
			break;
		case 2:
			m_pGameInstance->Play_Sound(L"VARG", L"FootStep_FullPlateA_03.ogg", SOUND_MonsterFootStep, 1.f);
			break;
		case 3:
			m_pGameInstance->Play_Sound(L"VARG", L"FootStep_FullPlateA_04.ogg", SOUND_MonsterFootStep, 1.f);
			break;
		}
	}


	if (m_iFootStepCheck < 0)
		m_iFootStepCheck = 10;
	return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
}

void CVarg_Walk_Front::Release(CVarg_GamePlay* pActor)
{
	__super::Release(pActor);
}