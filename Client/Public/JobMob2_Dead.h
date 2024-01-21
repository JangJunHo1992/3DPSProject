#pragma once
#include "State.h"
#include "JobMob2_Hurt.h"

BEGIN(Client)

class CJobMob2_Dead : public CJobMob2_Hurt
{
public:
	virtual void Initialize(CJobMob2_GamePlay* pActor) override;
	virtual CState<CJobMob2_GamePlay>* Update(CJobMob2_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CJobMob2_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CJobMob2::JobMob2State::Die1;
};

END
