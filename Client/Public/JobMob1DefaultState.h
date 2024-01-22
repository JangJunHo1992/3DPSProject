#pragma once
#include "State.h"
#include "JobMob1_GamePlay.h"

BEGIN(Engine)
class CGameInstance;
END

BEGIN(Client)

class CJobMob1DefaultState abstract : public CState<CJobMob1_GamePlay>
{
public:
	virtual void Initialize(CJobMob1_GamePlay* pActor) override;
	virtual CState<CJobMob1_GamePlay>* Update(CJobMob1_GamePlay* pActor, _float fTimeDelta) PURE;
	virtual void Release(CJobMob1_GamePlay* pActor) override;

public:
	CState<CJobMob1_GamePlay>* Ground_Normal(CJobMob1_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);

	CState<CJobMob1_GamePlay>* Run(CJobMob1_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);
	CState<CJobMob1_GamePlay>* Attack(CJobMob1_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);
	CState<CJobMob1_GamePlay>* Hitted(CJobMob1_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);


public:
	virtual CState<CJobMob1_GamePlay>* Update_State(CJobMob1_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex) PURE;

protected:
	CGameInstance* m_pGameInstance = { nullptr };
};

END