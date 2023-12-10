#pragma once

#include "VIBuffer_Terrain.h"

/* »ç°¢Çü. */

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Static_Terrain final : public CVIBuffer_Terrain
{
private:
	CVIBuffer_Static_Terrain(ID3D11Device * pDevice, ID3D11DeviceContext * pContext);
	CVIBuffer_Static_Terrain(const CVIBuffer_Static_Terrain& rhs);
	virtual ~CVIBuffer_Static_Terrain() = default;

public:
	virtual HRESULT Initialize_Prototype(const wstring & strHeightMapFilePath);
	virtual HRESULT Initialize(void* pArg) override;

public:
	static CVIBuffer_Static_Terrain* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, const wstring & strHeightMapFilePath);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END