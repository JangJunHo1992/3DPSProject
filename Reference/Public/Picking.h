#pragma once

#include "Engine_Defines.h"
#include "Component.h"
#include "Transform.h"
#include "VIBuffer_Terrain.h"


BEGIN(Engine)

class ENGINE_DLL CPicking : public CBase
{
	DECLARE_SINGLETON(CPicking)
private:
	CPicking() =default;
	virtual ~CPicking() = default;

public:
	HRESULT						Initialize(HWND _hWnd);
	void						Tick();

public:
	_bool						Intersect(_Out_ _float3& _vOut, const _float3 _vA, const _float3 _vB, const _float3 _vC, _In_opt_ const _float4x4 _mWorld =g_mUnit);

private:
	_float3						m_vRay[IDX(PICKER::MAX)]{};
	_float3						m_vOrg[IDX(PICKER::MAX)]{};

	HWND						m_hWnd = 0;

public:
	virtual void Free() override;
};

END