#include "stdafx.h"
#include "Magician_Attack4.h"
#include "GameInstance.h"


#include "Magician_Idle.h"

void CMagician_Attack4::Initialize(CMagician_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
	m_pGameInstance->Play_Sound(L"MAGICIAN", L"CV_MagicianLV2_AtkAction05_02.ogg", SOUND_EFFECT, 1.f);

}

CState<CMagician_GamePlay>* CMagician_Attack4::Update(CMagician_GamePlay* pActor, _float fTimeDelta)
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
	if (pActor->Is_Inputable_Front(25))
	{
		
		return new CMagician_Idle();
	}
	

	return nullptr;
}

void CMagician_Attack4::Release(CMagician_GamePlay* pActor)
{
	__super::Release(pActor);
}

