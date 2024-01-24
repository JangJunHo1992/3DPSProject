#pragma once
#include "State.h"
#include "JobMob2DefaultState.h"

BEGIN(Client)

class CJobMob2_Attack : public CJobMob2DefaultState
{
public:
	virtual void Initialize(CJobMob2_GamePlay* pActor) override;
	virtual CState<CJobMob2_GamePlay>* Update(CJobMob2_GamePlay* pActor, _float fTimeDelta) PURE;
	virtual void Release(CJobMob2_GamePlay* pActor) override;

public:
	virtual CState<CJobMob2_GamePlay>* Update_State(CJobMob2_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex) override;
};

END