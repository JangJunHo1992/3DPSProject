#pragma once
#include "State.h"
#include "Wizard_GamePlay.h"

BEGIN(Client)

class CWizard_Move_Walk_Stop : public CState<CWizard_GamePlay>
{
public:
	virtual void Initialize(CWizard_GamePlay* pActor) override;
	virtual CState<CWizard_GamePlay>* Update(CWizard_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CWizard_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CWizard_GamePlay::Wizard_State::Wizard_Move_Walk_Stop;
};

END