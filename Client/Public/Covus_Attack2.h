#pragma once
#include "Covus_Attack.h"

BEGIN(Client)

class CCovus_Attack2 : public CCovus_Attack
{
public:
	virtual void Initialize(CCovus_GamePlay* pActor) override;
	virtual CState<CCovus_GamePlay>* Update(CCovus_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CCovus_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CCovus::PlayerState::LAttatck2;
};

END