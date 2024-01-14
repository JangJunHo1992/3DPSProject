#pragma once
#include "State.h"
#include "VargDefaultState.h"

BEGIN(Client)

class CVarg_Attack : public CVargDefaultState
{
public:
	virtual void Initialize(CVarg_GamePlay* pActor) override;
	virtual CState<CVarg_GamePlay>* Update(CVarg_GamePlay* pActor, _float fTimeDelta) PURE;
	virtual void Release(CVarg_GamePlay* pActor) override;

public:
	virtual CState<CVarg_GamePlay>* Update_State(CVarg_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex) override;
};

END