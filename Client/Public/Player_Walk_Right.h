#pragma once
#include "State.h"
#include "Player_Walk.h"

BEGIN(Client)

class CPlayer_Walk_Right : public CPlayer_Walk
{
public:
	virtual void Initialize(CPlayer* pActor) override;
	virtual CState<CPlayer>* Update(CPlayer* pActor, _float fTimeDelta) override;
	virtual void Release(CPlayer* pActor) override;

public:
	static const _uint g_iAnimIndex = CPlayer::PlayerState::SD_WalkR;
};

END