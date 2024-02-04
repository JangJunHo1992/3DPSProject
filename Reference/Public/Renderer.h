#pragma once

#include "Base.h"

/* ȭ�鿡 �׷������� ��ü���� �׷����� ������� ��Ƴ��´�. */
/* ��Ƴ��� ������� ��ü���� �����Լ��� ȣ���Ѵ�.(������) */

BEGIN(Engine)
class CGameObject;
class CComponent;

class CRenderer final : public CBase
{
public:
	enum RENDERGROUP { RENDER_PRIORITY, RENDER_SHADOW, RENDER_NONLIGHT, RENDER_NONBLEND, RENDER_BLEND, RENDER_UI, RENDER_END };

private:
	CRenderer(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual ~CRenderer() = default;

public:
	HRESULT Initialize();
	HRESULT Add_RenderGroup(RENDERGROUP eGroupID, class CGameObject* pGameObject);
#ifdef _DEBUG
	HRESULT Add_DebugRender(class CComponent* pDebugCom);
#endif
	HRESULT Draw_RenderGroup();

private:
	ID3D11Device* m_pDevice = { nullptr };
	ID3D11DeviceContext* m_pContext = { nullptr };
	class CGameInstance* m_pGameInstance = { nullptr };
	list<CGameObject*>				m_RenderObjects[RENDER_END];

#ifdef _DEBUG
	list<CComponent*>					m_DebugComponent;
#endif
	LIGHT_DESC LightDesc = {};
private:
	class CShader* m_pShader = { nullptr };
	class CVIBuffer_Rect* m_pVIBuffer = { nullptr };

	_float4x4								m_WorldMatrix;
	_float4x4								m_ViewMatrix, m_ProjMatrix;
	ID3D11DepthStencilView* m_pLightDepthDSV = { nullptr };
private:
	HRESULT Render_Priority();
	HRESULT Render_Shadow();
	HRESULT Render_NonLight();
	HRESULT Render_NonBlend();
	HRESULT Render_Blend();
	HRESULT Render_UI();

	HRESULT Render_LightAcc();
	HRESULT Render_Deferred();

	HRESULT Render_Bloom();

#ifdef _DEBUG
private:
	HRESULT Render_Debug();
#endif	

public:
	static CRenderer* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual void Free() override;
};

END