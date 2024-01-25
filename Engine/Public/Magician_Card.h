#pragma once

#include "GameObject.h"

BEGIN(Engine)

class CCollider;
class CShader;

class ENGINE_DLL CMagician_Card abstract : public CGameObject
{
public:
	typedef struct
	{
		_float3 vStartPos = { 0.f, 0.f, 0.f };
		_float3 vEndPos = { 0.f, 0.f, 0.f };
		_float	fSpeed = { 0.f };

	}Magician_Card_DESC;

protected:
	CMagician_Card(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMagician_Card(const CMagician_Card& rhs);
	virtual ~CMagician_Card() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	virtual _bool Collision_Chcek() PURE;

protected:
	virtual HRESULT Ready_Components() PURE;
	virtual HRESULT Bind_ShaderResources();

protected:
	CCollider* m_pColliderCom = { nullptr };
	CShader* m_pShaderCom = { nullptr };
	CTexture* m_pTextureCom = { nullptr };
	_float3		m_vStartPos = { 0.f, 0.f, 0.f };
	_float3		m_vEndPos = { 0.f, 0.f, 0.f };
	_float		m_fSpeed = { 0.f };
	_float4x4	m_WorldMatrix = {};

	_float		m_fLifeTime = {150.f };





protected:
	virtual CGameObject* Clone(void* pArg) PURE;
	virtual void Free() override;


};

END