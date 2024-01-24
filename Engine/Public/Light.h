#pragma once

#include "Base.h"

BEGIN(Engine)

class CLight final : public CBase
{
private:
	CLight();
	virtual ~CLight() = default;

public:
	HRESULT Initialize(const LIGHT_DESC& LightDesc);
	HRESULT Render(class CShader* pShader, class CVIBuffer_Rect* pVIBuffer);

public:
	void Set_Lightpos(_float4 vLightPos) { m_vPos = vLightPos; }

private:
	LIGHT_DESC			m_LightDesc;
	_float4				m_vPos = { 0.f, 0.f, 0.f, 1.f };
public:
	static CLight* Create(const LIGHT_DESC& LightDesc);
	virtual void Free() override;
};

END