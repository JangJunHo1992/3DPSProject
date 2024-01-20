#include "..\Public\Massive_Greate_Sword_Move_Run.h"



void CMassive_Greate_Sword_Move_Run::Initialize(CDarkKnight_GamePlay* pActor)
{
	__super::Initialize(pActor);
}

void CMassive_Greate_Sword_Move_Run::Release(CDarkKnight_GamePlay* pActor)
{
	__super::Release(pActor);
}

CState<CDarkKnight_GamePlay>* CMassive_Greate_Sword_Move_Run::Update_State(CDarkKnight_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex)
{
	return Ground_Normal(pActor, fTimeDelta, _iAnimIndex);
}
