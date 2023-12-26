#pragma once
#include "State.h"
#include "DarkKnight_GamePlay.h"

BEGIN(Client)

class CMassive_Greate_Sword_JumpZ1 : public CState<CDarkKnight_GamePlay>
{
public:
	virtual void Initialize(CDarkKnight_GamePlay* pActor) override;
	virtual CState<CDarkKnight_GamePlay>* Update(CDarkKnight_GamePlay* pActor, _float fTimeDelta) override;
	virtual void Release(CDarkKnight_GamePlay* pActor) override;

public:
	static const _uint g_iAnimIndex = CDarkKnight::DarkKnight_State::Massive_Greate_Sword_JumpZ1;
};

END