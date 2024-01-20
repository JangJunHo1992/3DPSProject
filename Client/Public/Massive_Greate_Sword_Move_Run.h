#pragma once
#include "State.h"
#include "Massive_Greate_Sword_State.h"

BEGIN(Client)

class CMassive_Greate_Sword_Move_Run : public CMassive_Greate_Sword_State
{
public:
	virtual void Initialize(CDarkKnight_GamePlay* pActor) override;
	virtual CState<CDarkKnight_GamePlay>* Update(CDarkKnight_GamePlay* pActor, _float fTimeDelta) PURE;
	virtual void Release(CDarkKnight_GamePlay* pActor) override;

public:
	virtual CState<CDarkKnight_GamePlay>* Update_State(CDarkKnight_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex) override;
};

END