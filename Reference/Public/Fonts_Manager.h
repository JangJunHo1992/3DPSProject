#pragma once

#include "Base.h"

BEGIN(Engine)
class CFonts;

class CFonts_Manager final : public CBase
{
private:
	CFonts_Manager(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual ~CFonts_Manager() = default;

public:
	HRESULT Initialize();
	HRESULT Add_Font(const wstring& strFontTag, const wstring& strFontFilePath);
	HRESULT Render(const wstring& strFontTag, const wstring& strText, const _float2 & vPosition, _fvector vColor, _float fScale, _float2 vOrigin = _float2(0.f, 0.f), _float fRotation = 0.f);

private:
	ID3D11Device* m_pDevice = { nullptr };
	ID3D11DeviceContext* m_pContext = { nullptr };
	map<const wstring, CFonts*>		m_Fonts;

private:
	CFonts* Find_Font(const wstring & strFontTag);

public:
	static CFonts_Manager* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext);
	virtual void Free() override;
};

END