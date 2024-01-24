#pragma once
#include "Varg_Attack.h"

BEGIN(Client)

class CVarg_Attack1_3 : public CVarg_Attack
{
public:
	virtual void Initialize(CVarg_GamePlay* pActor) override;
	virtual CState<CVarg_GamePlay>* Update(CVarg_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CVarg_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CVarg::VargState::ComboAttack1_3;
};

END