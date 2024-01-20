#pragma once
#include "State.h"
#include "KnightGuard_GamePlay.h"

BEGIN(Client)

class CSpear_Shield_Down_Wall_Liedown_Down : public CState<CKnightGuard_GamePlay>
{
public:
	virtual void Initialize(CKnightGuard_GamePlay* pActor) override;
	virtual CState<CKnightGuard_GamePlay>* Update(CKnightGuard_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CKnightGuard_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CKnightGuard::KnightGuard_State::Spear_Shield_Down_Wall_Liedown_Down;
};

END