#include "..\Public\GreatDualBlade_Run.h"



void CGreatDualBlade_Run::Initialize(CRaider_GamePlay* pActor)
{
	__super::Initialize(pActor);
}

void CGreatDualBlade_Run::Release(CRaider_GamePlay* pActor)
{
	__super::Release(pActor);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Run::Update_State(CRaider_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
