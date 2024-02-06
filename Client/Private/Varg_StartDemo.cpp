#include "stdafx.h"
#include "Varg_StartDemo.h"
#include "GameInstance.h"
#include "Varg_Idle.h"
#include "Boss_HPBarBase.h"
#include "Boss_HPBar.h"

void CVarg_StartDemo::Initialize(CVarg_GamePlay* pActor)
{
	__super::Initialize(pActor);

	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CVarg_GamePlay>* CVarg_StartDemo::Update(CVarg_GamePlay* pActor, _float fTimeDelta)
{

	if (pActor->Is_Animation_End())
	{
		pActor->Set_StartScene(false);

		{
			CBoss_HPBarBase::Boss_HPBarBase_DESC		BackGroundDesc = {};


			BackGroundDesc.fX = 640;
			BackGroundDesc.fY = 50;
			BackGroundDesc.fSizeX = 400;
			BackGroundDesc.fSizeY = 30;
			BackGroundDesc.fRotationPerSec = XMConvertToRadians(90.f);
			BackGroundDesc.fSpeedPerSec = 10.f;
			m_pGameInstance->Add_CloneObject(LEVEL_BOSS1, TEXT("Layer_UI"), TEXT("Prototype_GameObject_TexUI_Boss_HPBarBase"), &BackGroundDesc);
			
		}
		{
			CBoss_HPBar::Boss_HPBar_DESC		BackGroundDesc = {};


			BackGroundDesc.fX = 640;
			BackGroundDesc.fY = 50;
			BackGroundDesc.fSizeX = 293;
			BackGroundDesc.fSizeY = 18;
			BackGroundDesc.fRotationPerSec = XMConvertToRadians(90.f);
			BackGroundDesc.fSpeedPerSec = 10.f;
			m_pGameInstance->Add_CloneObject(LEVEL_BOSS1, TEXT("Layer_UI"), TEXT("Prototype_GameObject_TexUI_Boss_HPBar"), &BackGroundDesc);
			
		}
		return new CVarg_Idle();

	}


	return nullptr;

}

void CVarg_StartDemo::Release(CVarg_GamePlay* pActor)
{
	__super::Release(pActor);
}