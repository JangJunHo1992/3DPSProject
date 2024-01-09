#pragma once
#include "State.h"
#include "Varg_GamePlay.h"

BEGIN(Engine)
class CGameInstance;
END

BEGIN(Client)

class CVargDefaultState abstract : public CState<CVarg_GamePlay>
{
public:
	virtual void Initialize(CVarg_GamePlay* pActor) override;
	virtual CState<CVarg_GamePlay>* Update(CVarg_GamePlay* pActor, _float fTimeDelta) PURE;
	virtual void Release(CVarg_GamePlay* pActor) override;

public:
	CState<CVarg_GamePlay>* Ground_Normal(CVarg_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);

	CState<CVarg_GamePlay>* Run(CVarg_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);
	CState<CVarg_GamePlay>* Dash(CVarg_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);
	CState<CVarg_GamePlay>* Hitted(CVarg_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex);


public:
	virtual CState<CVarg_GamePlay>* Update_State(CVarg_GamePlay* pActor, _float fTimeDelta, _uint _iAnimIndex) PURE;

protected:
	CGameInstance* m_pGameInstance = { nullptr };
};

END