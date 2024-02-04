#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CTrail final : public CVIBuffer
{

public:
	typedef struct TrailDesc
{
	_uint _iVertex_Count = 0;
	_float3 _vUp = _float3(0.f,0.f,0.f);
	_float _fItv = 0.f;
	_matrix worldmat;
	_int	TrailType = 0;
}TRAILDESC;
protected:
	CTrail(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CTrail(const CTrail& _pPrototype);
	virtual ~CTrail();

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* _pInfo);
	virtual	HRESULT	Render_Trail();

	void	Trail_Update(_matrix matWorld, _float3 vDir, _float fLength);
	void	Trail_NoFull(_matrix matWorld, _float3 vDir, _float fLength);
	void	Set_Render(_bool bIsRender) {
		m_bIsRender = bIsRender;
	}

public:
	static CTrail* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CComponent* Clone(void* _pInfo = nullptr);

private:
		virtual	void Free();

private:
	TRAILDESC		m_Traildesc;
	_uint m_iVBCount = 0;
	_uint m_iCatmullRomSize = 20;
	_bool m_bIsRender = false;
	vector<_float3>	m_vecStart;
	vector<_float3>	m_vecEnd;
	vector<_float3>	m_vecCatStart;
	vector<_float3>	m_vecCatEnd;
};

END

