#pragma once

#include "Component.h"

BEGIN(Engine)

class CCell;
class CNavigationPoint;

class ENGINE_DLL CNavigation final : public CComponent
{
public:
	typedef struct tagNaviDesc
	{
		_int		iCurrentIndex;
	}NAVI_DESC;
private:
	CNavigation(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CNavigation(const CNavigation& rhs);
	virtual ~CNavigation() = default;

public:
	CCell* Get_CurrentCell();
	_float Get_CurrentHeight(_fvector vPosition);

public:
	virtual HRESULT Initialize_Prototype(const wstring & strNavigationFilePath);
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Render();

public:
	HRESULT Make_Cell_By_Points(CNavigationPoint * pPoint1, CNavigationPoint * pPoint2, CNavigationPoint * pPoint3);
	CNavigationPoint* Make_Point(_float3 vPos);
	CNavigationPoint* Select_Point(RAY ray);

	
	HRESULT Save_All();

public:
	void Update(_fmatrix WorldMatrix, _float fTimeDelta);
	_bool isMove(_fvector vPosition);

private:
	_uint m_iPointIndex	= 0;
	_uint m_iCellIndex	= 0;

	vector<CNavigationPoint*>	m_Points;
	vector<CCell*>			m_Cells;
	static _float4x4				m_WorldMatrix;
	_int							m_iCurrentIndex = { -1 };


#ifdef _DEBUG
private:
	class CShader* m_pShader = { nullptr };
#endif

private:
	HRESULT Make_Neighbors();
	
	vector<_float3> Make_Points_Clockwise(_float3 vPoints[3], _bool & bIsCounterclockwise);


public:
	static CNavigation* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, const wstring & strNavigationFilePath);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END