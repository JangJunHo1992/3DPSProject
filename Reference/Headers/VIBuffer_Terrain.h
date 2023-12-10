#pragma once

#include "VIBuffer.h"

/* »ç°¢Çü. */

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Terrain abstract : public CVIBuffer
{
protected:
	CVIBuffer_Terrain(ID3D11Device * pDevice, ID3D11DeviceContext * pContext);
	CVIBuffer_Terrain(const CVIBuffer_Terrain& rhs);
	virtual ~CVIBuffer_Terrain() = default;

public:
	virtual HRESULT Initialize_Prototype(const wstring & strHeightMapFilePath) PURE;
	virtual HRESULT Initialize(void* pArg) override;

protected:
	_uint				m_iNumVerticesX = { 0 };
	_uint				m_iNumVerticesZ = { 0 };

	//VTXMESH*			m_pVertices = { nullptr };
	//_uint*				m_pIndices	= { nullptr };

public:
	//static CVIBuffer_Terrain* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, const wstring & strHeightMapFilePath);
	//virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END