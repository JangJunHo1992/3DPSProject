#pragma once

#include "Body_Client.h"

BEGIN(Client)

class CRaider_Body abstract : public CBody_Client
{
protected:
	CRaider_Body(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CRaider_Body(const CRaider_Body& rhs);
	virtual ~CRaider_Body() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

protected:
	virtual HRESULT Ready_Components() PURE;
	virtual HRESULT Ready_Components_Origin(LEVEL eLevel) override;
	virtual HRESULT Bind_ShaderResources() override;

public:
	virtual void Free() override;
};

END