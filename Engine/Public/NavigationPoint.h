#pragma once

#include "GameObject.h"


BEGIN(Engine)
class CCollider;
class CTransform;

class ENGINE_DLL CNavigationPoint final : public CGameObject
{
public:
	typedef struct tagNavigationPointDesc
	{
		tagNavigationPointDesc() {}
		tagNavigationPointDesc(_float3 _vPos)
			: vPos(_vPos) {}

		_float3	vPos = { 0.f, 0.f, 0.f };

	}NAVIGATION_POINT_DESC;

public:
	CNavigationPoint(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CNavigationPoint(const CNavigationPoint& rhs);
	virtual ~CNavigationPoint() = default;

public:
	vector<_uint>* Get_ParentIndexes() {
		return &m_ParentIndex;
	}
	void Add_ParentIndex(_uint	_iParentIndex) {
		m_ParentIndex.push_back(_iParentIndex);
	}

	_uint Get_Index() {
		return m_iIndex;
	}

	void Set_Index(_uint _iIndex) {
		m_iIndex = _iIndex;
	}

	_bool IsSelected(RAY ray);

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	CCollider* m_pColliderCom = { nullptr };
	vector<_uint>	m_ParentIndex;
	_uint	m_iIndex = { 0 };

public:
	/* 원형객체를 생성한다. */
	static CNavigationPoint* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, void* pArg);

	// CGameObject을(를) 통해 상속됨
	virtual CNavigationPoint* Clone(void* pArg) override;

	virtual void Free() override;


};

END