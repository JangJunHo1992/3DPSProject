#pragma once

#include "Magician_Weapon.h"

BEGIN(Client)

class CMagician_Card :public CMagician_Weapon
{
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
	virtual _bool Collision_Chcek();
	virtual void Start_Ranged_Attack(const _vector& vDirection);
	virtual void Update_Ranged_Attack(_float fTimeDelta);
protected:
	virtual HRESULT Ready_Components() PURE;
	virtual HRESULT Ready_Components_Origin(LEVEL eLevel);
	virtual HRESULT Bind_ShaderResources();
protected:
	CShader*			m_pShaderCom = { nullptr };
	CTexture*			m_pTextureCom = { nullptr };
	class CCharacter*	m_pPlayer = { nullptr };
	class CCollider*	m_pColliderCom = { nullptr };
	_vector				m_vAttackDirection; // 원거리 공격 방향
	_float				m_fAttackSpeed = 0;       // 원거리 공격 속도
	_int				CardCheckTime = 200;
	_uint				m_iColliderSize = { 0 };
	_vector				vPos = {};
	_bool				m_bfirstcheck = true;
public:
	virtual void Free() override;

};

END