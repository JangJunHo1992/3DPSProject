#pragma once
#include "State.h"
#include "Covus_GamePlay.h"

BEGIN(Client)

class CCovus_Dead : public CState<CCovus_GamePlay>
{
public:
	virtual void Initialize(CCovus_GamePlay* pActor) override;
	virtual CState<CCovus_GamePlay>* Update(CCovus_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CCovus_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CCovus::PlayerState::Dead_1;
};

END

