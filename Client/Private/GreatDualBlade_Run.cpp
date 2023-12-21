#include "..\Public\GreatDualBlade_Run.h"



void CGreatDualBlade_Run::Initialize(CRaider_GamePlay* pActor)
{
	__super::Initialize(pActor);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Run::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	//return Run(pActor, g_iAn);
	return nullptr;
}

void CGreatDualBlade_Run::Release(CRaider_GamePlay* pActor)
{
	__super::Release(pActor);
}
