#pragma once

#include "Client_Defines.h"
#include "AlphaObject.h"

BEGIN(Engine)
class CVIBuffer_Trail;
class CTexture;
class CShader;
class CBone;
END

BEGIN(Client)

class CEffect_Trail : public CAlphaObject
{
protected:
	CEffect_Trail(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CEffect_Trail(const CEffect_Trail& rhs);
	virtual ~CEffect_Trail() = default;

public:
	void Set_TimeScaleLayer(const _uint& In_iTimeScaleLayer) {
		m_iTimeScaleLayerIndex = In_iTimeScaleLayer;
	}

protected:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	void Update(_float fTimeDelta, _matrix _ParentMatrix);
	void Set_OwnerDesc(_matrix _ParentMatrix);
	void Set_TextureIndex(_uint In_iDiffuseIndex, _uint In_iMaskIndex, _uint In_iNoiseIndex)
	{
		m_iDiffuseIndex = In_iDiffuseIndex;
		m_iMaskIndex = In_iMaskIndex;
		m_iNoiseIndex = In_iNoiseIndex;
	}

	void Set_Use(_bool _bIsUse) {
		m_bIsUse = _bIsUse;
	}

	_bool Get_Use() {
		return m_bIsUse;
	}

private:
	HRESULT Ready_Components(LEVEL eLevel);
	HRESULT Bind_ShaderResources();

protected:
	_uint m_iTimeScaleLayerIndex = { 0 };
	_float4x4 m_pParentMatrix;
	CShader* m_pShader = { nullptr };

	CVIBuffer_Trail* m_pVIBuffer = { nullptr };

	CTexture* m_pTextureCom = { nullptr };
	CTexture* m_pMaskTextureCom = { nullptr };
	CTexture* m_pNoiseTextureCom = { nullptr };

	_uint m_iDiffuseIndex = { 0 };
	_uint m_iMaskIndex = { 0 };
	_uint m_iNoiseIndex = { 0 };

	_bool m_bIsUse = { true };

	_uint m_iPass = { 2 };



private:
	_float				m_fFrame = { 0.0f };



public:
	static CEffect_Trail* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg) override;
	void Free();

};

END

