#pragma once
#include "State.h"
#include "Player_Dash.h"

BEGIN(Client)

class CPlayer_Dash_Front : public CPlayer_Dash
{
public:
	virtual void Initialize(CPlayer* pActor) override;
	virtual CState<CPlayer>* Update(CPlayer* pActor, _float fTimeDelta) override;
	virtual void Release(CPlayer* pActor) override;

public:
	static const _uint g_iAnimIndex = CPlayer::PlayerState::Pw_Darts_A_F_V1;
};

END