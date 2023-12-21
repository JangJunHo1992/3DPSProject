#pragma once
#include "State.h"
#include "King_GamePlay.h"

BEGIN(Client)

class CTwoHandedHammerSet_Attack_1H_Around2 : public CState<CKing_GamePlay>
{
public:
	virtual void Initialize(CKing_GamePlay* pActor) override;
	virtual CState<CKing_GamePlay>* Update(CKing_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CKing_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CKing::King_State::TwoHandedHammerSet_Attack_1H_Around2;
};

END