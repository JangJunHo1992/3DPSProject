#pragma once

#include "Weapon_Client.h"

BEGIN(Client)

class CCovus_Weapon abstract : public CWeapon_Client
{
protected:
	CCovus_Weapon(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CCovus_Weapon(const CCovus_Weapon& rhs);
	virtual ~CCovus_Weapon() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	virtual _bool Collision_Chcek();
	virtual _bool Collision_Chcekb1();
	virtual _bool Collision_Chcekb2();

protected:
	virtual HRESULT Ready_Components() PURE;
	virtual HRESULT Ready_Components_Origin(LEVEL eLevel) override;
	virtual HRESULT Bind_ShaderResources() override;
private:
	_uint	m_iCurrentLevel;
public:
	virtual void Free() override;

};

END