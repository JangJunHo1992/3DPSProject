#pragma once
#include "State.h"
#include "MagicianDefaultState.h"

BEGIN(Client)

class CMagician_Shoot : public CMagicianDefaultState
{
public:
	virtual void Initialize(CMagician_GamePlay* pActor) override;
	virtual CState<CMagician_GamePlay>* Update(CMagician_GamePlay* pActor, _float fTimeDelta) PURE;
	virtual void Release(CMagician_GamePlay* pActor) override;

public:
	virtual CState<CMagician_GamePlay>* Update_State(CMagician_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex) override;
};

END