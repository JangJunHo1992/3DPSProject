#pragma once
#include "State.h"
#include "Player_Run.h"

BEGIN(Client)

class CCovus_Idle : public CCovus_Run
{
public:
	virtual void Initialize(CCovus_GamePlay* pActor) override;
	virtual CState<CCovus_GamePlay>* Update(CCovus_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CCovus_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CCovus::PlayerState::Idle;
};

END