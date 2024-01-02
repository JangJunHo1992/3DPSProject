#include "stdafx.h"
#include "Covus_Dead.h"
#include "GameInstance.h"

void CCovus_Dead::Initialize(CCovus_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CCovus_GamePlay>* CCovus_Dead::Update(CCovus_GamePlay* pActor, _float fTimeDelta)
{
	return __super::Update(pActor,fTimeDelta);
}

void CCovus_Dead::Release(CCovus_GamePlay* pActor)
{
}
