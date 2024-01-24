#pragma once
#include "State.h"
#include "JobMob2_Walk.h"

BEGIN(Client)

class CJobMob2_Walk_Front : public CJobMob2_Walk
{
public:
	virtual void Initialize(CJobMob2_GamePlay* pActor) override;
	virtual CState<CJobMob2_GamePlay>* Update(CJobMob2_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CJobMob2_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CJobMob2::JobMob2State::Run_N;
};

END