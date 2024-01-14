#pragma once
#include "Varg_Attack.h"

BEGIN(Client)

class CVarg_RaidAttack2 : public CVarg_Attack
{
public:
	virtual void Initialize(CVarg_GamePlay* pActor) override;
	virtual CState<CVarg_GamePlay>* Update(CVarg_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CVarg_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CVarg::VargState::RaidAttack2;
};

END