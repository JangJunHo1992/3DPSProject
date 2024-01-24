#pragma once
#include "State.h"
#include "DefaultState.h"

BEGIN(Client)

class CCovus_Recover : public CDefaultState
{
public:
	virtual void Initialize(CCovus_GamePlay* pActor) override;
	virtual CState<CCovus_GamePlay>* Update(CCovus_GamePlay* pActor, _float fTimeDelta) PURE;
	virtual void Release(CCovus_GamePlay* pActor) override;

public:
	virtual CState<CCovus_GamePlay>* Update_State(CCovus_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex) override;
};

END