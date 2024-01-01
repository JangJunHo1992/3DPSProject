#include "stdafx.h"
#include "GreatDualBlade_Defense_Start.h"
#include "GameInstance.h"

#include "GreatDualBlade_Defense_Loop.h"
#include "GreatDualBlade_Defense_End.h"



void CGreatDualBlade_Defense_Start::Initialize(CRaider_GamePlay* pActor)
{
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CRaider_GamePlay>* CGreatDualBlade_Defense_Start::Update(CRaider_GamePlay* pActor, _float fTimeDelta)
{
	if (CGameInstance::GetInstance()->Key_Pressing(DIK_X)) 
	{
		if (pActor->Is_Animation_End())
		{
			return new CGreatDualBlade_Defense_Loop();
		}
	}
	else 
	{
		return new CGreatDualBlade_Defense_End();
	}
	
	return nullptr;
}

void CGreatDualBlade_Defense_Start::Release(CRaider_GamePlay* pActor)
{
	
}