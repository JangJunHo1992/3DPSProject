#pragma once
#include "State.h"
#include "Magician_Hurt.h"

BEGIN(Client)

class CMagician_Stun : public CMagician_Hurt
{
public:
	virtual void Initialize(CMagician_GamePlay* pActor) override;
	virtual CState<CMagician_GamePlay>* Update(CMagician_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CMagician_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CMagician::MagicianState::StunStart_Cane;
};

END
