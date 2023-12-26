#pragma once
#include "State.h"
#include "KnightGuard_GamePlay.h"

BEGIN(Client)

class CSpear_Shield_Defence_Strafe_Walk_Front_R45 : public CState<CKnightGuard_GamePlay>
{
public:
	virtual void Initialize(CKnightGuard_GamePlay* pActor) override;
	virtual CState<CKnightGuard_GamePlay>* Update(CKnightGuard_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CKnightGuard_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CKnightGuard::KnightGuard_State::Spear_Shield_Defence_Strafe_Walk_Front_R45;
};

END