#include "stdafx.h"
#include "Magician_DisappearB.h"
#include "GameInstance.h"


void CMagician_DisappearB::Initialize(CMagician_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true, true);
	_uint iRandom = rand() % 3;
	switch (iRandom)
	{
	case 0:
		m_pGameInstance->Play_Sound(L"MAGICIAN", L"Magician_ClothMagic_01.ogg", SOUND_MonsterFootStep, 1.f);
		break;
	case 1:
		m_pGameInstance->Play_Sound(L"MAGICIAN", L"Magician_ClothMagic_02.ogg", SOUND_MonsterFootStep, 1.f);
		break;
	case 2:
		m_pGameInstance->Play_Sound(L"MAGICIAN", L"Magician_ClothMagic_03.ogg", SOUND_MonsterFootStep, 1.f);
		break;

	}
}

CState<CMagician_GamePlay>* CMagician_DisappearB::Update(CMagician_GamePlay* pActor, _float fTimeDelta)
{
	/*pActor->Go_Backward(fTimeDelta);*/
	if (pActor->Is_Inputable_Back(10))
	{
		
		return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
	}

	return nullptr;
}

void CMagician_DisappearB::Release(CMagician_GamePlay* pActor)
{
	__super::Release(pActor);
}