#pragma once
#include "State.h"
#include "Magician_Walk.h"

BEGIN(Client)

class CMagician_Walk_Right : public CMagician_Walk
{
public:
	virtual void Initialize(CMagician_GamePlay* pActor) override;
	virtual CState<CMagician_GamePlay>* Update(CMagician_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CMagician_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CMagician::MagicianState::WalkR;
};

END
