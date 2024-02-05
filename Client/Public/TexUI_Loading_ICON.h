#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CTexture;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CTexUI_Loading_ICON final : public CGameObject
{
public:
	typedef struct tagTexUI_Loading_ICONDesc : public CGameObject::GAMEOBJECT_DESC
	{
		_float			fX, fY, fSizeX, fSizeY;
	}TexUI_Loading_ICON_DESC;

private:
	CTexUI_Loading_ICON(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CTexUI_Loading_ICON(const CTexUI_Loading_ICON& rhs);
	virtual ~CTexUI_Loading_ICON() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;
private:
	_float				m_fX, m_fY, m_fSizeX, m_fSizeY;
	_float4x4			m_ViewMatrix, m_ProjMatrix;

private:
	CShader* m_pShaderCom = { nullptr };
	CTexture* m_pTextureCom = { nullptr };
	CVIBuffer_Rect* m_pVIBufferCom = { nullptr };

private:
	HRESULT Ready_Components();
	HRESULT Bind_ShaderResources();

public:
	/* 원형객체를 생성한다. */
	static CTexUI_Loading_ICON* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;
};

END
