#pragma once
#include "State.h"
#include "Covus_Hurt.h"

BEGIN(Client)

class CCovus_CutScene1 : public CCovus_Hurt
{
public:
	virtual void Initialize(CCovus_GamePlay* pActor) override;
	virtual CState<CCovus_GamePlay>* Update(CCovus_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CCovus_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CCovus::PlayerState::SD_VSvarg_Execution;
};

END


