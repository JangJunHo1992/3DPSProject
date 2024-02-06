#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CModel;
class CCollider;
END

BEGIN(Client)

class CMagician_Card_Bullet abstract : public CGameObject
{
protected:
	CMagician_Card_Bullet(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMagician_Card_Bullet(const CMagician_Card_Bullet& rhs);
	virtual ~CMagician_Card_Bullet() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	CParticle_Custom::PARTICLE_DESC Get_Particle_Blood_Desc();
	CParticle_Custom::PARTICLE_DESC Get_Particle_HalfMoon_Desc();
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	//virtual void Write_Json(json& Out_Json) override;

protected:
	CShader*		m_pShaderCom = { nullptr };
	CModel*			m_pModelCom = { nullptr };
	CCollider*		m_pColliderCom = { nullptr };

	_float4x4		m_WorldMatrix = {};

	_vector				m_vPlayerPos = {};
	_vector				m_vMonsterPos = {};
	_int				m_iCardDeadTime = 1000;
public:
	virtual _bool Collision_Chcek();

	void Create_Attack_Particle(LEVEL eLevel, _float3 vLocalPos);

	
protected:
	virtual HRESULT Ready_Components() PURE;
	HRESULT Ready_Components_Origin(LEVEL eLEVEL);
	HRESULT Bind_ShaderResources();


public:
	///* 원형객체를 생성한다. */
	//static CMagician_Card_Bullet* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	///* 사본객체를 생성한다. */
	//virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;
};

END