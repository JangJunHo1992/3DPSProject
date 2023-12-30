#pragma once
#include "State.h"
#include "Covus_GamePlay.h"

BEGIN(Engine)
class CGameInstance;
END

BEGIN(Client)

class CDefaultState abstract : public CState<CCovus_GamePlay>
{
public:
	virtual void Initialize(CCovus_GamePlay* pActor) override;
	virtual CState<CCovus_GamePlay>* Update(CCovus_GamePlay* pActor, _float fTimeDelta) PURE;
	virtual void Release(CCovus_GamePlay* pActor) override;

public:
	CState<CCovus_GamePlay>* Ground_Normal(CCovus_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);

	CState<CCovus_GamePlay>* Run(CCovus_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);
	CState<CCovus_GamePlay>* Dash(CCovus_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);
	CState<CCovus_GamePlay>* Walk(CCovus_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);
	CState<CCovus_GamePlay>* Hitted(CCovus_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);


public:
	virtual CState<CCovus_GamePlay>* Update_State(CCovus_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex) PURE;

protected:
	CGameInstance* m_pGameInstance = { nullptr };
};

END