#pragma once

//#include "Client_Defines.h"
#include "Body_Client.h"


BEGIN(Client)

class CBody_Player : public CBody_Client
{
protected:
	CBody_Player(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CBody_Player(const CBody_Player& rhs);
	virtual ~CBody_Player() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;


protected:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Ready_Components_Origin(LEVEL eLevel) override;
	virtual HRESULT Bind_ShaderResources() override;


public:
	/* 원형객체를 생성한다. */
	static CBody_Player* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;
};

END