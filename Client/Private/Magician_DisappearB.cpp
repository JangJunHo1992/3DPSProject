#include "stdafx.h"
#include "Magician_DisappearB.h"
#include "GameInstance.h"


void CMagician_DisappearB::Initialize(CMagician_GamePlay* pActor)
{
	__super::Initialize(pActor);
	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true, true);
}

CState<CMagician_GamePlay>* CMagician_DisappearB::Update(CMagician_GamePlay* pActor, _float fTimeDelta)
{
	/*pActor->Go_Backward(fTimeDelta);*/
	if (pActor->Is_Inputable_Back(10))
	{
		return __super::Update_State(pActor, fTimeDelta, g_iAnimIndex);
	}
	return nullptr;
}

void CMagician_DisappearB::Release(CMagician_GamePlay* pActor)
{
	__super::Release(pActor);
}