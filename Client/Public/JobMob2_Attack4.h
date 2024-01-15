#pragma once
#include "JobMob2_Attack.h"

BEGIN(Client)

class CJobMob2_Attack4 : public CJobMob2_Attack
{
public:
	virtual void Initialize(CJobMob2_GamePlay* pActor) override;
	virtual CState<CJobMob2_GamePlay>* Update(CJobMob2_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CJobMob2_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CJobMob2::JobMob2State::Attack4;
};

END