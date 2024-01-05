#pragma once
#include "Covus_Hurt.h"

BEGIN(Client)

class CCovus_HurtMFR : public CCovus_Hurt
{
public:
	virtual void Initialize(CCovus_GamePlay* pActor) override;
	virtual CState<CCovus_GamePlay>* Update(CCovus_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CCovus_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CCovus::PlayerState::HurtMFR;
};

END