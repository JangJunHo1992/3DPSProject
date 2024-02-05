#pragma once

#include "Weapon_Client.h"

BEGIN(Client)

class CJobMob2_Weapon abstract : public CWeapon_Client
{
protected:
	CJobMob2_Weapon(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CJobMob2_Weapon(const CJobMob2_Weapon& rhs);
	virtual ~CJobMob2_Weapon() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	virtual _bool Collision_Chcek();

	void Create_Attack_Particle(LEVEL eLevel, _float3 vLocalPos);

protected:
	virtual HRESULT Ready_Components() PURE;
	virtual HRESULT Ready_Components_Origin(LEVEL eLevel) override;
	virtual HRESULT Bind_ShaderResources() override;

public:
	virtual void Free() override;

};

END