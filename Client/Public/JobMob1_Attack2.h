#pragma once
#include "JobMob1_Attack.h"

BEGIN(Client)

class CJobMob1_Attack2 : public CJobMob1_Attack
{
public:
	virtual void Initialize(CJobMob1_GamePlay* pActor) override;
	virtual CState<CJobMob1_GamePlay>* Update(CJobMob1_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CJobMob1_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CJobMob1::JobMob1State::ComboB01;
};

END