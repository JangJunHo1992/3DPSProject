#pragma once
#include "State.h"
#include "Golem_GamePlay.h"

BEGIN(Client)

class CGiant_Golem_Atk_L_foot : public CState<CGolem_GamePlay>
{
public:
	virtual void Initialize(CGolem_GamePlay* pActor) override;
	virtual CState<CGolem_GamePlay>* Update(CGolem_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CGolem_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CGolem::Golem_State::Giant_Golem_Atk_L_foot;
};

END