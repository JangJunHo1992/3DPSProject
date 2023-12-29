#pragma once
#include "State.h"
#include "DefaultState.h"

BEGIN(Client)

class CPlayer_Dash : public CDefaultState
{
public:
	virtual void Initialize(CPlayer* pActor) override;
	virtual CState<CPlayer>* Update(CPlayer* pActor, _float fTimeDelta) PURE;
	virtual void Release(CPlayer* pActor) override;

public:
	virtual CState<CPlayer>* Update_State(CPlayer* pActor, _float fTimeDelta, _uint _iAnimIndex) override;
};

END