#pragma once

#include "Base.h"

BEGIN(Engine)

class CLayer final : public CBase
{
private:
	CLayer();
	virtual ~CLayer() = default;

public:
	class CComponent* Get_Component(const wstring& strComponentTag, _uint iIndex);

public:
	HRESULT Add_GameObject(class CGameObject* pGameObject);
	void Priority_Tick(_float fTimeDelta);
	void Tick(_float fTimeDelta);
	void Late_Tick(_float fTimeDelta);

public:
	list<CGameObject*>*	Get_GameObjects() { return &m_GameObjects; };

private:
	list<CGameObject*>			m_GameObjects;
	_uint						m_iCheckTime;
public:
	static CLayer* Create();
	virtual void Free() override;
};

END