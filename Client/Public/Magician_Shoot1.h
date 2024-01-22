#pragma once
#include "Magician_Shoot.h"

BEGIN(Client)

class CMagician_Shoot1 : public CMagician_Shoot
{
public:
	virtual void Initialize(CMagician_GamePlay* pActor) override;
	virtual CState<CMagician_GamePlay>* Update(CMagician_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CMagician_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CMagician::MagicianState::Shoot1;
};

END