#include "Covus_Recover.h"



void CCovus_Recover::Initialize(CCovus_GamePlay* pActor)
{
	__super::Initialize(pActor);
}

void CCovus_Recover::Release(CCovus_GamePlay* pActor)
{
	__super::Release(pActor);
}

CState<CCovus_GamePlay>* CCovus_Recover::Update_State(CCovus_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
