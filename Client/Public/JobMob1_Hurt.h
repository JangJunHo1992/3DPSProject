#pragma once
#include "State.h"
#include "JobMob1DefaultState.h"

BEGIN(Client)

class CJobMob1_Hurt : public CJobMob1DefaultState
{
public:
	virtual void Initialize(CJobMob1_GamePlay* pActor) override;
	virtual CState<CJobMob1_GamePlay>* Update(CJobMob1_GamePlay* pActor, _float fTimeDelta) PURE;
	virtual void Release(CJobMob1_GamePlay* pActor) override;

public:
	virtual CState<CJobMob1_GamePlay>* Update_State(CJobMob1_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex) override;
};

END