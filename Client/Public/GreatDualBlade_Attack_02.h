#pragma once
#include "State.h"
#include "Raider_GamePlay.h"

BEGIN(Client)

class CGreat_DualBlade_Attack_02 : public CState<CRaider_GamePlay>
{
public:
	virtual void Initialize(CRaider_GamePlay* pActor) override;
	virtual CState<CRaider_GamePlay>* Update(CRaider_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CRaider_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CRaider::Raider_State::Great_DualBlade_anim_attack_02;
};

END