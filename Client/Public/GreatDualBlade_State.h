#pragma once
#include "State.h"
#include "Raider_GamePlay.h"

BEGIN(Engine)
class CGameInstance;
END

BEGIN(Client)

class CGreatDualBlade_State abstract : public CState<CRaider_GamePlay>
{
public:
	virtual void Initialize(CRaider_GamePlay* pActor) override;
	virtual CState<CRaider_GamePlay>* Update(CRaider_GamePlay* pActor, _float fTimeDelta) PURE;
	virtual void Release(CRaider_GamePlay* pActor) override;

public:
	CState<CRaider_GamePlay>* Ground_Normal(CRaider_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);

	CState<CRaider_GamePlay>* Run(CRaider_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);
	CState<CRaider_GamePlay>* Roll(CRaider_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);

	CState<CRaider_GamePlay>* Hitted(CRaider_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);


public:
	virtual CState<CRaider_GamePlay>* Update_State(CRaider_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex) PURE;

protected:
	CGameInstance* m_pGameInstance = { nullptr };
};

END