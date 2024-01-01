#pragma once
#include "State.h"
#include "GreatDualBlade_Run.h"

BEGIN(Client)

class CGreatDualBlade_Run_Right : public CGreatDualBlade_Run
{
public:
	virtual void Initialize(CRaider_GamePlay* pActor) override;
	virtual CState<CRaider_GamePlay>* Update(CRaider_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CRaider_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CRaider::Raider_State::Great_DualBlade_anim_run_right;
};

END