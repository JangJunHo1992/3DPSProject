#pragma once

#include "Weapon.h"
#include "Client_Defines.h"
#include "Particle_Custom.h"

BEGIN(Client)
class CEffect_Trail;

class CWeapon_Client abstract : public CWeapon
{
protected:
	CWeapon_Client(ID3D11Device* pDevice, ID3D11DeviceContext* pContext) 
		: CWeapon (pDevice, pContext)
	{
	};
	CWeapon_Client(const CWeapon_Client& rhs) 
		: CWeapon(rhs)
	{
	};
	virtual ~CWeapon_Client() = default;
public:
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Late_Tick(_float fTimeDelta) override;
public:
	CParticle_Custom::PARTICLE_DESC Get_Particle_Blood_Desc();
	CParticle_Custom::PARTICLE_DESC Get_Particle_HitEffect_Desc();
	CParticle_Custom::PARTICLE_DESC Get_Particle_HalfMoon_Desc();
protected:
	CEffect_Trail* m_pTrailDiffuse = { nullptr };
protected:
	virtual HRESULT Ready_Components_Origin(LEVEL eLevel) PURE;

};

END