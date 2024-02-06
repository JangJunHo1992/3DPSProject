#include "Player_Dash.h"
#include "GameInstance.h"


void CCovus_Dash::Initialize(CCovus_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Parry(true);
	m_pGameInstance->Play_Sound(L"ENEMY_FOOTSTEP", L"BossBat_WingFlap_01.ogg", SOUND_EFFECT2, 1.f);

}

void CCovus_Dash::Release(CCovus_GamePlay* pActor)
{
	__super::Release(pActor);
	pActor->Set_Parry(false);

}

CState<CCovus_GamePlay>* CCovus_Dash::Update_State(CCovus_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
