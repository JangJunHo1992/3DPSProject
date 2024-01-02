#include "Fonts_Manager.h"
#include "Fonts.h"

CFonts_Manager::CFonts_Manager(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: m_pDevice(pDevice)
	, m_pContext(pContext)
{
	Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pContext);
}

HRESULT CFonts_Manager::Initialize()
{
	return S_OK;
}


HRESULT CFonts_Manager::Add_Font(const wstring& strFontTag, const wstring& strFontFilePath)
{
	if (nullptr != Find_Font(strFontTag))
		return E_FAIL;

	CFonts* pFont = CFonts::Create(m_pDevice, m_pContext, strFontFilePath);
	if (nullptr == pFont)
		return E_FAIL;

	m_Fonts.emplace(strFontTag, pFont);

	return S_OK;
}

HRESULT CFonts_Manager::Render(const wstring& strFontTag, const wstring& strText, const _float2& vPosition, _fvector vColor, _float fScale, _float2 vOrigin, _float fRotation)
{
	CFonts* pFont = Find_Font(strFontTag);

	if (nullptr == pFont)
		return E_FAIL;

	return pFont->Render(strText, vPosition, vColor, fScale, vOrigin, fRotation);
}

CFonts* CFonts_Manager::Find_Font(const wstring& strFontTag)
{
	auto	iter = m_Fonts.find(strFontTag);

	if (iter == m_Fonts.end())
		return nullptr;

	return iter->second;
}

CFonts_Manager* CFonts_Manager::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CFonts_Manager* pInstance = new CFonts_Manager(pDevice, pContext);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CFont_Manager");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CFonts_Manager::Free()
{
	for (auto& Pair : m_Fonts)
		Safe_Release(Pair.second);

	m_Fonts.clear();

	Safe_Release(m_pDevice);
	Safe_Release(m_pContext);
}
