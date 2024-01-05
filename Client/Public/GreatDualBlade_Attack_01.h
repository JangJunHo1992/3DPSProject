#pragma once
#include "GreatDualBlade_Attack.h"

BEGIN(Client)

class CGreat_DualBlade_Attack_01 : public CGreatDualBlade_Attack
{
public:
	virtual void Initialize(CRaider_GamePlay* pActor) override;
	virtual CState<CRaider_GamePlay>* Update(CRaider_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CRaider_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CRaider::Raider_State::Great_DualBlade_anim_attack_01;
};

END