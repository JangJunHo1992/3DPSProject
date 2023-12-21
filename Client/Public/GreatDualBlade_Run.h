#pragma once
#include "State.h"
#include "GreatDualBlade_State.h"

BEGIN(Client)

class CGreatDualBlade_Run : public CGreatDualBlade_State
{
public:
	virtual void Initialize(CRaider_GamePlay* pActor) override;
	virtual CState<CRaider_GamePlay>* Update(CRaider_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CRaider_GamePlay* pActor) override;

//protected:
//	_uint	
};

END