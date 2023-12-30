#pragma once
#include "State.h"
#include "Player_Walk.h"

BEGIN(Client)

class CCovus_Walk_Front : public CCovus_Walk
{
public:
	virtual void Initialize(CCovus_GamePlay* pActor) override;
	virtual CState<CCovus_GamePlay>* Update(CCovus_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CCovus_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CCovus::PlayerState::SD_WalkF;
};

END