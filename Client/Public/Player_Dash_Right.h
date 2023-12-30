#pragma once
#include "State.h"
#include "Player_Dash.h"

BEGIN(Client)

class CCovus_Dash_Right : public CCovus_Dash
{
public:
	virtual void Initialize(CCovus_GamePlay* pActor) override;
	virtual CState<CCovus_GamePlay>* Update(CCovus_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CCovus_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CCovus::PlayerState::Pw_Darts_A_R_V1;
};

END