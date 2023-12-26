#include "stdafx.h"
#include "GreatDualBlade_Defense_Loop.h"
#include "GameInstance.h"

#include "GreatDualBlade_Defense_End.h"


void CGreatDualBlade_Defense_Loop::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_LOOP, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Defense_Loop::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (CGameInstance::GetInstance()->Key_Up(DIK_X)) 
	{
		return new CGreatDualBlade_Defense_End();
	}

	return nullptr;
}

void CGreatDualBlade_Defense_Loop::Release(CRaider_GamePlay* pActor)
{
	
}