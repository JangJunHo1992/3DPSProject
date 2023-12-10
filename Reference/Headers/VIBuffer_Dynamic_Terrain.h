#pragma once

#include "VIBuffer_Terrain.h"

/* »ç°¢Çü. */

BEGIN(Engine)

class CGameInstance;

class ENGINE_DLL CVIBuffer_Dynamic_Terrain final : public CVIBuffer_Terrain
{
private:
	CVIBuffer_Dynamic_Terrain(ID3D11Device * pDevice, ID3D11DeviceContext * pContext);
	CVIBuffer_Dynamic_Terrain(const CVIBuffer_Dynamic_Terrain& rhs);
	virtual ~CVIBuffer_Dynamic_Terrain() = default;

public:
	virtual HRESULT Initialize_Prototype(const wstring & strHeightMapFilePath);
	virtual HRESULT Initialize(void* pArg) override;

public:
	_bool			Picking(RAY ray, _float3 * out);
	void			Invalidate_Terrain(_vector _vMousePos, _float _fRadious, _float _fPower);

private:
	CGameInstance* m_pGameInstance = nullptr;

	VTXMESH*			m_pVertices = { nullptr };
	_uint*				m_pIndices	= { nullptr };

public:
	static CVIBuffer_Dynamic_Terrain* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, const wstring & strHeightMapFilePath);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END