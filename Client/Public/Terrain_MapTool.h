#pragma once
#include "Terrain.h"
#include "IPick.h"

BEGIN(Client)
class CMap_Window;

class CTerrain_MapTool final : public CTerrain, public IPick
{

protected:
	CTerrain_MapTool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CTerrain_MapTool(const CTerrain_MapTool& rhs);
	virtual ~CTerrain_MapTool() = default;

private:
	virtual HRESULT Ready_Components() override;
	HRESULT Initialize_CreateBuffer(void* pArg);

public:
	/* 원형객체를 생성한다. */
	static CTerrain_MapTool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) override;


	// IPick을(를) 통해 상속됨
	virtual void pick() override;

	// CTerrain을(를) 통해 상속됨
	virtual HRESULT Bind_ShaderResources() override;

public:
	//_float	GetBrushRange() { return m_fBrushRange; }
	void	Set_BrushRange(_float _fBrushRange) { m_fBrushRange = _fBrushRange; }
	void	Set_BrushHeight(_float _fBrushHeight) { m_fBrushHeight = _fBrushHeight; }
public:
	_float* Get_BrushRangePoint() { return &m_fBrushRange; }
	_float* Get_BrushHeightPoint() { return &m_fBrushHeight; }
	_int*  Get_BrushMode() { return &m_iMode; }
	_float3	Get_PickedPosFloat3() { return m_vPickedPosFloat3; };
public:
	void	Update_MousePos();


private:
	_vector m_vPickedPos = { 0.f, 0.f, 0.f, 0.f };
	_float3	m_vPickedPosFloat3 = { 0.f, 0.f, 0.f };
	_float	m_fBrushRange = { 5.f };
	_float  m_fBrushHeight = { 1.f };
	_int	m_iMode	= { 0 };
};

END