#pragma once
#include "State.h"
#include "Varg_Walk.h"

BEGIN(Client)

class CVarg_Walk_Front : public CVarg_Walk
{
public:
	virtual void Initialize(CVarg_GamePlay* pActor) override;
	virtual CState<CVarg_GamePlay>* Update(CVarg_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CVarg_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CVarg::VargState::WalkF;
};

END