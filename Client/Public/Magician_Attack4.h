
#pragma once
#include "Magician_Attack.h"

BEGIN(Client)

class CMagician_Attack4 : public CMagician_Attack
{
public:
	virtual void Initialize(CMagician_GamePlay* pActor) override;
	virtual CState<CMagician_GamePlay>* Update(CMagician_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CMagician_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CMagician::MagicianState::Stage2_Attack04;
};

END