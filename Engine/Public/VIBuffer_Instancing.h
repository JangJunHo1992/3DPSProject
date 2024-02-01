#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Instancing abstract : public CVIBuffer
{
public:
	typedef struct
	{
		_float3		vCenter = _float3(0.f, 0.f, 0.f);
		_float3		vCulling = _float3(0.f, 0.f, 0.f);
		_float3		vDestination = _float3(0.f, 0.f, 0.f);

		_float2		vRange = _float2(0.f, 2.f);

		_float2		vRotationX = _float2(0.f, 360.f);
		_float2		vRotationY = _float2(0.f, 360.f);
		_float2		vRotationZ = _float2(0.f, 360.f);

		_float2		vSpeed = _float2(0.1f, 1.0f);
		_float		fAcceleration = { 0.0f };
		_float2		vScaleX = _float2(0.1f, 0.3f);
		_float2		vScaleY = _float2(0.1f, 0.3f);

		_float2		vLifeTime = _float2(0.0f, 1.4f);
	}INSTANCING_DESC;

protected:
	CVIBuffer_Instancing(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CVIBuffer_Instancing(const CVIBuffer_Instancing& rhs);
	virtual ~CVIBuffer_Instancing() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Bind_VIBuffers() override;
	virtual void Update(_float fTimeDelta);
	virtual HRESULT Render();


protected:
	ID3D11Buffer* m_pVBInstance = { nullptr };
	_uint						m_iInstanceStride = { 0 };
	_uint						m_iNumInstance = { 0 };
	_uint						m_iIndexCountPerInstance = { 0 };

protected:
	random_device				m_RandomDevice;
	mt19937_64					m_RandomNumber;

protected:
	_float* m_pSpeeds = { nullptr };
	_float						m_fAccelerations = { 0.f };

	_float* m_pLifeTimes = { nullptr };
	INSTANCING_DESC				m_InstancingDesc;
	_float						m_fTimeAcc = { 0.0f };

public:
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END