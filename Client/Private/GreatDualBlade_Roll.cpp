#include "..\Public\GreatDualBlade_Roll.h"
#include "GreatDualBlade_Idle.h"

void CGreatDualBlade_Roll::Initialize(CRaider_GamePlay* pActor)
{
	__super::Initialize(pActor);
}

void CGreatDualBlade_Roll::Release(CRaider_GamePlay* pActor)
{
	__super::Release(pActor);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Roll::Update_State(CRaider_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	if (pActor->Is_Animation_End())
	{
		return new CGreatDualBlade_Idle();
	}
	return nullptr;
}
