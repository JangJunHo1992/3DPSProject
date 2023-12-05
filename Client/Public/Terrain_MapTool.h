#pragma once
#include "Terrain.h"

BEGIN(Client)

class CTerrain_MapTool final : public CTerrain
{

protected:
	CTerrain_MapTool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CTerrain_MapTool(const CTerrain_MapTool& rhs);
	virtual ~CTerrain_MapTool() = default;

private:
	virtual HRESULT Ready_Components() override;

public:
	/* ������ü�� �����Ѵ�. */
	static CTerrain_MapTool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;


	// CTerrain��(��) ���� ��ӵ�
	virtual HRESULT Bind_ShaderResources() override;

public:
	//_float	GetBrushRange() { return m_fBrushRange; }
	void	Set_BrushRange(_float _fBrushRange) { m_fBrushRange = _fBrushRange; }
	_float3	Get_PickedPosFloat3() { return m_vPickedPosFloat3; };

	void	Update_MousePos();


private:
	_vector m_vPickedPos = { 0.f, 0.f, 0.f, 0.f };
	_float3	m_vPickedPosFloat3 = { 0.f, 0.f, 0.f };
	_float	m_fBrushRange = { 30.f };

};

END