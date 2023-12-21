#pragma once
#include "Terrain.h"

BEGIN(Client)

class CTerrain_Tool final : public CTerrain
{
	
protected:
	CTerrain_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CTerrain_Tool(const CTerrain_Tool& rhs);
	virtual ~CTerrain_Tool() = default;


private:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Bind_ShaderResources() override;

public:
	void Change_Plane_Buffer(_ushort x, _ushort z);

	
public:
	virtual HRESULT Initialize(void* pArg) override;
	void pick();

public:
	//_float   GetBrushRange() { return m_fBrushRange; }
	void   Set_BrushRange(_float _fBrushRange) { m_fBrushRange = _fBrushRange; }
	void   Set_BrushHeight(_float _fBrushHeight) { m_fBrushHeight = _fBrushHeight; }
public:
	_float* Get_BrushRangePoint() { return &m_fBrushRange; }
	_float* Get_BrushHeightPoint() { return &m_fBrushHeight; }
	_int* Get_BrushMode() { return &m_iMode; }
	_float3   Get_PickedPosFloat3() { return m_vPickedPosFloat3; };

	void	Update_MousePos();
	


//public:
//	virtual void Write_Json(json& Out_Json) override;
//	virtual void Load_FromJson(const json& In_Json) override;

private:
	_vector m_vPickedPos = { 0.f, 0.f, 0.f, 0.f };
	_float3   m_vPickedPosFloat3 = { 0.f, 0.f, 0.f };
	_float   m_fBrushRange = { 5.f };
	_float  m_fBrushHeight = { 1.f };
	_int   m_iMode = { -1 };

	class CGameInstance* m_pGameInstance = nullptr;


public:
public:
	/* 원형객체를 생성한다. */
	static CTerrain_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, _bool isPlane = false);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;

};

END