#pragma once

#include "Base.h"

BEGIN(Engine)
class CLight;

class CLight_Manager final : public CBase
{
private:
	CLight_Manager();
	virtual ~CLight_Manager() = default;

public:
	HRESULT Initialize();
	HRESULT Add_Light(const LIGHT_DESC& LightDesc);

	HRESULT Render(class CShader* pShader, class CVIBuffer_Rect* pVIBuffer);
public:
	CLight* Get_Light_Back() { return m_Lights.back();}

private:
	list<CLight*>			m_Lights;

public:
	static CLight_Manager* Create();
	virtual void Free() override;
};

END