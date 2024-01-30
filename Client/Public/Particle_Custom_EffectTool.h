#pragma once

#include "Client_Defines.h"
#include "GameObject.h"
#include "Particle_Custom.h"


BEGIN(Client)

class CParticle_Custom_EffectTool final : public CParticle_Custom
{

private:
	CParticle_Custom_EffectTool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CParticle_Custom_EffectTool(const CParticle_Custom_EffectTool& rhs);
	virtual ~CParticle_Custom_EffectTool() = default;

private:
	virtual HRESULT Ready_Components();

public:
	/* 원형객체를 생성한다. */
	static CParticle_Custom_EffectTool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;
};

END