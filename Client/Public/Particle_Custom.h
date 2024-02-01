#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CTexture;
class CVIBuffer_Particle_Point;
END

BEGIN(Client)

class CParticle_Custom : public CGameObject
{
public:
	typedef struct tagParticleDesc : public CGameObject::GAMEOBJECT_DESC
	{
		CVIBuffer_Particle_Point::PARTICLE_POINT_DESC		ParticleDesc = {};
		_matrix parentMatrix;
		_float3 vPos;
	}PARTICLE_DESC;

protected:
	CParticle_Custom(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CParticle_Custom(const CParticle_Custom& rhs);
	virtual ~CParticle_Custom() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

protected:
	CShader* m_pShaderCom = { nullptr };
	CTexture* m_pTextureCom = { nullptr };
	CVIBuffer_Particle_Point* m_pVIBufferCom = { nullptr };
	CVIBuffer_Particle_Point::PARTICLE_POINT_DESC		m_ParticleDesc = {};
	_float			m_fTimeAcc = { 0.0f };
protected:
	virtual HRESULT Ready_Components(LEVEL eLevel);
	HRESULT Bind_ShaderResources();


public:
	/* 원형객체를 생성한다. */
	static CParticle_Custom* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;
};

END