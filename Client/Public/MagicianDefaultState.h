#pragma once
#include "State.h"
#include "Magician_GamePlay.h"

BEGIN(Engine)
class CGameInstance;
END

BEGIN(Client)

class CMagicianDefaultState abstract : public CState<CMagician_GamePlay>
{
public:
	virtual void Initialize(CMagician_GamePlay* pActor) override;
	virtual CState<CMagician_GamePlay>* Update(CMagician_GamePlay* pActor, _float fTimeDelta) PURE;
	virtual void Release(CMagician_GamePlay* pActor) override;

public:
	CState<CMagician_GamePlay>* Ground_Normal(CMagician_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);

	CState<CMagician_GamePlay>* Attack(CMagician_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);
	CState<CMagician_GamePlay>* Shoot(CMagician_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);
	CState<CMagician_GamePlay>* Walk(CMagician_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);
	CState<CMagician_GamePlay>* Hitted(CMagician_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);
	CState<CMagician_GamePlay>* Disappear(CMagician_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);

public:
	_int	m_iFootStepCheck = 25;

public:
	virtual CState<CMagician_GamePlay>* Update_State(CMagician_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex) PURE;

protected:
	CGameInstance* m_pGameInstance = { nullptr };
};

END