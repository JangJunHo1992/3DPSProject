#pragma once

#include "Magician_Disappear.h"

BEGIN(Client)

class CMagician_DisappearR : public CMagician_Disappear
{
public:
	virtual void Initialize(CMagician_GamePlay* pActor) override;
	virtual CState<CMagician_GamePlay>* Update(CMagician_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CMagician_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CMagician::MagicianState::DisappearMove_R;
};

END