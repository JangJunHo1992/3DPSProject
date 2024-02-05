#include "stdafx.h"
#include "Covus_Parry.h"



void CCovus_Parry::Initialize(CCovus_GamePlay* pActor)
{
	__super::Initialize(pActor);
	
	pActor->Set_Parry(true);
}

void CCovus_Parry::Release(CCovus_GamePlay* pActor)
{
	__super::Release(pActor);
	
	pActor->Set_Parry(false);

}

CState<CCovus_GamePlay>* CCovus_Parry::Update_State(CCovus_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
