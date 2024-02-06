#include "stdafx.h"
#include "Magician_Attack5.h"
#include "GameInstance.h"


#include "Magician_Idle.h"

void CMagician_Attack5::Initialize(CMagician_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
	m_pGameInstance->Play_Sound(L"MAGICIAN", L"CV_MagicianLV2_AtkAction09.ogg", SOUND_EFFECT, 1.f);

}

CState<CMagician_GamePlay>* CMagician_Attack5::Update(CMagician_GamePlay* pActor, _float fTimeDelta)
{
	_uint iMinimumPlayTime = 10;
	// 
	if (pActor->Is_Inputable_Front(20))
	{
		pActor->Set_IsAttack(true);
	}
	if (pActor->Is_Inputable_Back(30))
	{
		pActor->Set_IsAttack(false);
	}

	if (pActor->Is_Animation_End())
	{
		
		return new CMagician_Idle();
	}
	

	return nullptr;
}

void CMagician_Attack5::Release(CMagician_GamePlay* pActor)
{
	__super::Release(pActor);
}

