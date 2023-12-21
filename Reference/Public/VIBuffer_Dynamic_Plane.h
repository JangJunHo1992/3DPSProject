#pragma once

#include "VIBuffer_Dynamic_Terrain_Origin.h"

/* »ç°¢Çü. */

BEGIN(Engine)

class CGameInstance;

class ENGINE_DLL CVIBuffer_Dynamic_Plane final : public CVIBuffer_Dynamic_Terrain_Origin
{
private:
	CVIBuffer_Dynamic_Plane(ID3D11Device * pDevice, ID3D11DeviceContext * pContext);
	CVIBuffer_Dynamic_Plane(const CVIBuffer_Dynamic_Plane& rhs);
	virtual ~CVIBuffer_Dynamic_Plane() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize_Prototype(const wstring & strHeightMapFilePath) { return S_OK; };

	virtual HRESULT Initialize(void* pArg) override;

public:
	void	Set_Size(_ushort _iSizeX, _ushort _iSizeZ);

private:
	_ushort		m_iSizeX = { 0 };
	_ushort		m_iSizeZ = { 0 };


public:
	static CVIBuffer_Dynamic_Plane* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, _ushort x, _ushort z);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END