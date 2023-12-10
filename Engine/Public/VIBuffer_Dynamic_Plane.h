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
	virtual HRESULT Initialize_Prototype(_ushort x, _ushort z);
	virtual HRESULT Initialize_Prototype(const wstring & strHeightMapFilePath) { return S_OK; };

	virtual HRESULT Initialize(void* pArg) override;


public:
	static CVIBuffer_Dynamic_Plane* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, _ushort x, _ushort z);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END