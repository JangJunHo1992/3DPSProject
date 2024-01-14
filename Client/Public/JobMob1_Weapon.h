#pragma once

#include "Weapon_Client.h"

BEGIN(Client)

class CJobMob1_Weapon abstract : public CWeapon_Client
{
protected:
	CJobMob1_Weapon(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CJobMob1_Weapon(const CJobMob1_Weapon& rhs);
	virtual ~CJobMob1_Weapon() = default;

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