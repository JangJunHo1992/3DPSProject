#pragma once
#include "VIBuffer.h"

BEGIN(Engine)

class CGameObject;
class CTransform;
class CBone;


class ENGINE_DLL CVIBuffer_Trail : public CVIBuffer
{
private:
	CVIBuffer_Trail(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CVIBuffer_Trail(const CVIBuffer_Trail& rhs);
	virtual ~CVIBuffer_Trail() = default;

protected:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	void Update(_float _fTimeDelta, _matrix _ParentMatrix);
	void Tick(_float fTimeDelta);

public:
	void Reset_Points(_matrix _ParentMatrix);


protected:
	_bool m_bTrailOn;
	_uint m_iVtxCnt;
	_uint m_iNumVertices;
	_float4 m_vLocalSwordLow;
	_float4 m_vLocalSwordHigh;
	TRAIL_DESC m_tTrailDesc;

	_uint m_iLerpPointNum = 12;
	_int m_iCatMullRomIndex[4];

public:
	static CVIBuffer_Trail* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CComponent* Clone(void* pArg) override;
	void Free();
};

END