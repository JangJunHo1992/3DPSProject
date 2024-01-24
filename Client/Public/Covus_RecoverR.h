#pragma once
#include "State.h"
#include "Covus_Recover.h"

BEGIN(Client)

class CCovus_RecoverR : public CCovus_Recover
{
public:
	virtual void Initialize(CCovus_GamePlay* pActor) override;
	virtual CState<CCovus_GamePlay>* Update(CCovus_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CCovus_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CCovus::PlayerState::QuicklyRecoverUp_R;
};

END