#include "..\Public\GreatDualBlade_Attack.h"



void CGreatDualBlade_Attack::Initialize(CRaider_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_IsAttack(true);
}

void CGreatDualBlade_Attack::Release(CRaider_GamePlay* pActor)
{
	__super::Release(pActor);
	pActor->Set_IsAttack(false);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Attack::Update_State(CRaider_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
