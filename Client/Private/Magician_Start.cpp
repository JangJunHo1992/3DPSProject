#include "stdafx.h"
#include "Magician_Start.h"
#include "GameInstance.h"
#include "Magician_Idle.h"
#include "Boss_HPBarBase.h"
#include "Boss_HPBar2.h"

void CMagician_Start::Initialize(CMagician_GamePlay* pActor)
{
	__super::Initialize(pActor);

	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CMagician_GamePlay>* CMagician_Start::Update(CMagician_GamePlay* pActor, _float fTimeDelta)
{
	if (pActor->Is_Animation_End())
	{
		{
			CBoss_HPBarBase::Boss_HPBarBase_DESC		BackGroundDesc = {};

			BackGroundDesc.fX = 640;
			BackGroundDesc.fY = 50;
			BackGroundDesc.fSizeX = 400;
			BackGroundDesc.fSizeY = 30;
			BackGroundDesc.fRotationPerSec = XMConvertToRadians(90.f);
			BackGroundDesc.fSpeedPerSec = 10.f;
			m_pGameInstance->Add_CloneObject(LEVEL_BOSS2, TEXT("Layer_UI"), TEXT("Prototype_GameObject_TexUI_Boss_HPBarBase"), &BackGroundDesc);
		
		}

		{
			CBoss_HPBar2::Boss_HPBar2_DESC		BackGroundDesc = {};


			BackGroundDesc.fX = 640;
			BackGroundDesc.fY = 50;
			BackGroundDesc.fSizeX = 293;
			BackGroundDesc.fSizeY = 18;
			BackGroundDesc.fRotationPerSec = XMConvertToRadians(90.f);
			BackGroundDesc.fSpeedPerSec = 10.f;
			m_pGameInstance->Add_CloneObject(LEVEL_BOSS2, TEXT("Layer_UI"), TEXT("Prototype_GameObject_TexUI_Boss_HPBar2"), &BackGroundDesc);
			
		}
		pActor->Set_StartScene2(false);
		return new CMagician_Idle();
	}
}

void CMagician_Start::Release(CMagician_GamePlay* pActor)
{
	__super::Release(pActor);
}