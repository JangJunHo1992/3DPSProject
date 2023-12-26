#pragma once

#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CModel;
class CBone;

class ENGINE_DLL CWeapon abstract : public CGameObject
{
public:
	typedef struct
	{
		class CBone* m_pSocketBone = { nullptr };
		class CTransform* m_pParentTransform = { nullptr };
	}WEAPON_DESC;

protected:
	CWeapon(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CWeapon(const CWeapon& rhs);
	virtual ~CWeapon() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

protected:
	CShader* m_pShaderCom = { nullptr };
	CModel* m_pModelCom = { nullptr };

protected:
	class CTransform* m_pParentTransform = { nullptr };
	class CBone* m_pSocketBone = { nullptr };
	_float4x4	m_WorldMatrix = {};

protected:
	virtual HRESULT Ready_Components() PURE;
	virtual HRESULT Bind_ShaderResources();


public:
	///* 원형객체를 생성한다. */
	//static CWeapon* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) PURE;

	virtual void Free() override;
};

END