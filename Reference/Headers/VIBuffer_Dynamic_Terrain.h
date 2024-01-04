#pragma once

#include "VIBuffer_Dynamic_Terrain_Origin.h"

/* »ç°¢Çü. */

BEGIN(Engine)

class CGameInstance;

class ENGINE_DLL CVIBuffer_Dynamic_Terrain final : public CVIBuffer_Dynamic_Terrain_Origin
{
private:
	CVIBuffer_Dynamic_Terrain(ID3D11Device * pDevice, ID3D11DeviceContext * pContext);
	CVIBuffer_Dynamic_Terrain(const CVIBuffer_Dynamic_Terrain& rhs);
	virtual ~CVIBuffer_Dynamic_Terrain() = default;

public:
	virtual HRESULT Initialize_Prototype(const wstring & strHeightMapFilePath);
	virtual HRESULT Initialize(void* pArg) override;


public:
	static CVIBuffer_Dynamic_Terrain* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, const wstring & strHeightMapFilePath);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END