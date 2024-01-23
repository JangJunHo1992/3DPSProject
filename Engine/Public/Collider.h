#pragma once

#include "Component.h"

#include "Bounding_AABB.h"
#include "Bounding_OBB.h"
#include "Bounding_Sphere.h"

/* �浹ü. */
/* �浹ü�� �����ϴ� ��� + �浹ü�� �׸��� ��� + �浹�� ���ϴ� ��� . */

BEGIN(Engine)

class CGameObject;

class ENGINE_DLL CCollider final : public CComponent
{
public:
	enum TYPE { TYPE_SPHERE, TYPE_AABB, TYPE_OBB, TYPE_END };

private:
	CCollider(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CCollider(const CCollider& rhs);
	virtual ~CCollider() = default;

public:
	TYPE Get_ColliderType() const {
		return m_eType;
	}

	class CBounding* Get_Bounding() {
		return m_pBounding;
	}

public:
	virtual HRESULT Initialize_Prototype(TYPE eType);
	virtual HRESULT Initialize(void* pArg);

public:
	void Update(_fmatrix TransformMatrix);
	_bool Collision(CCollider* pTargetCollider);

	_vector& GetCenterPos() { return m_vCenterPos; }
	_vector* GetAxisDir() { return m_vAxisDir; }
	float* GetAxisLen() { return m_fAxisLen; }
public:
	_vector		m_vCenterPos; //���� �߾� ��ǥ
	_vector		m_vAxisDir[3]; // ���ڿ� ������ ������ ���� ����
	_float		m_fAxisLen[3]; // ������ ������ �� ���� ���� fAxisLen[n]�� vAxisDir[n]�� ���� �����Ѵ�.

//public:
//	void Set_Owner(CGameObject* pOwner);

#ifdef _DEBUG
public:
	HRESULT Render();
#endif

private:
	TYPE					m_eType = { TYPE_END };
	class CBounding*		m_pBounding = { nullptr };
	_bool					m_isCollision = { false };

	CGameObject*			m_pOwner = { nullptr };

#ifdef _DEBUG
private:
	PrimitiveBatch<VertexPositionColor>* m_pBatch = { nullptr };
	BasicEffect* m_pEffect = { nullptr };
	ID3D11InputLayout* m_pInputLayout = { nullptr };
#endif


public:
	static CCollider* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, TYPE eType);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END