#pragma once

#include "Weapon_Client.h"

BEGIN(Client)

class CMagician_Weapon abstract : public CWeapon_Client
{
protected:
	CMagician_Weapon(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMagician_Weapon(const CMagician_Weapon& rhs);
	virtual ~CMagician_Weapon() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	virtual _bool Collision_Chcek();

protected:
	virtual HRESULT Ready_Components() PURE;
	virtual HRESULT Ready_Components_Origin(LEVEL eLevel) override;
	virtual HRESULT Bind_ShaderResources() override;

public:
	virtual void Free() override;

};

END