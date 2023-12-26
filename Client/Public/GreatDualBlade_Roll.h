#pragma once
#include "State.h"
#include "GreatDualBlade_State.h"

BEGIN(Client)

class CGreatDualBlade_Roll : public CGreatDualBlade_State
{
public:
	virtual void Initialize(CRaider_GamePlay* pActor) override;
	virtual CState<CRaider_GamePlay>* Update(CRaider_GamePlay* pActor, _float fTimeDelta) PURE;
	virtual void Release(CRaider_GamePlay* pActor) override;

public:
	virtual CState<CRaider_GamePlay>* Update_State(CRaider_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex) override;
};

END