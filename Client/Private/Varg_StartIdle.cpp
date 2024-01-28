#include "stdafx.h"
#include "Varg_StartIdle.h"
#include "GameInstance.h"
#include "Varg_StartDemo.h"



void CVarg_StartIdle::Initialize(CVarg_GamePlay* pActor)
{
	__super::Initialize(pActor);

	pActor->Set_Animation(g_iAnimIndex, CModel::ANIM_STATE_NORMAL, true);
}

CState<CVarg_GamePlay>* CVarg_StartIdle::Update(CVarg_GamePlay* pActor, _float fTimeDelta)
{
	
	if (pActor->Is_Animation_End())
	{
		if (40.f < pActor->Calc_Distance() && pActor->Get_bCheckStart() == true)//나중에 오브젝트 넣어서 그거 파괴하면 보스랑 싸우게 할거면 이거로 해도됨! 
		{
			pActor->Set_bCheckStart(false);
			pActor->m_bStartScene = true; // 이거 카메라 
			return new CVarg_StartDemo();

		}
	}


	return nullptr;
	
}

void CVarg_StartIdle::Release(CVarg_GamePlay* pActor)
{
	__super::Release(pActor);
}