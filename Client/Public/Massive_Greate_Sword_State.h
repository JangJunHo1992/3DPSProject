#pragma once
#include "State.h"
#include "DarkKnight_GamePlay.h"

BEGIN(Engine)
class CGameInstance;
END

BEGIN(Client)

class CMassive_Greate_Sword_State abstract : public CState<CDarkKnight_GamePlay>
{
public:
	virtual void Initialize(CDarkKnight_GamePlay* pActor) override;
	virtual CState<CDarkKnight_GamePlay>* Update(CDarkKnight_GamePlay* pActor, _float fTimeDelta) PURE;
	virtual void Release(CDarkKnight_GamePlay* pActor) override;

public:
	CState<CDarkKnight_GamePlay>* Ground_Normal(CDarkKnight_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);

	CState<CDarkKnight_GamePlay>* Run(CDarkKnight_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);
	CState<CDarkKnight_GamePlay>* Roll(CDarkKnight_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);

	CState<CDarkKnight_GamePlay>* Hitted(CDarkKnight_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);


public:
	virtual CState<CDarkKnight_GamePlay>* Update_State(CDarkKnight_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex) PURE;

protected:
	CGameInstance* m_pGameInstance = { nullptr };
};

END