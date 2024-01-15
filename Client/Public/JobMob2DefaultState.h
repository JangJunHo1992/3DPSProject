#pragma once
#include "State.h"
#include "JobMob2_GamePlay.h"

BEGIN(Engine)
class CGameInstance;
END

BEGIN(Client)

class CJobMob2DefaultState abstract : public CState<CJobMob2_GamePlay>
{
public:
	virtual void Initialize(CJobMob2_GamePlay* pActor) override;
	virtual CState<CJobMob2_GamePlay>* Update(CJobMob2_GamePlay* pActor, _float fTimeDelta) PURE;
	virtual void Release(CJobMob2_GamePlay* pActor) override;

public:
	CState<CJobMob2_GamePlay>* Ground_Normal(CJobMob2_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);

	CState<CJobMob2_GamePlay>* Run(CJobMob2_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);
	CState<CJobMob2_GamePlay>* Attack(CJobMob2_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);
	CState<CJobMob2_GamePlay>* RaidAttack(CJobMob2_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);
	CState<CJobMob2_GamePlay>* Hitted(CJobMob2_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);


public:
	virtual CState<CJobMob2_GamePlay>* Update_State(CJobMob2_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex) PURE;

protected:
	CGameInstance* m_pGameInstance = { nullptr };
};

END