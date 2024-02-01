#pragma once

#include "Client_Defines.h"
#include "AlphaObject.h"

BEGIN(Engine)
class CShader;
class CTexture;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CEffect_Fire final : public CAlphaObject
{
private:
	CEffect_Fire(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CEffect_Fire(const CEffect_Fire& rhs);
	virtual ~CEffect_Fire() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	CShader* m_pShaderCom = { nullptr };
	CTexture* m_pTextureCom = { nullptr };
	CVIBuffer_Rect* m_pVIBufferCom = { nullptr };

private:
	_float				m_fFrame = { 0.0f };

private:
	HRESULT Ready_Components();
	HRESULT Bind_ShaderResources();

	void Write_Json(json& Out_Json);


public:
	/* 원형객체를 생성한다. */
	static CEffect_Fire* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;
};

END