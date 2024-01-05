#pragma once
#include "Covus_Parry.h"

BEGIN(Client)

class CCovus_Parry_L : public CCovus_Parry
{
public:
	virtual void Initialize(CCovus_GamePlay* pActor) override;
	virtual CState<CCovus_GamePlay>* Update(CCovus_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CCovus_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CCovus::PlayerState::ParryL;
};

END
