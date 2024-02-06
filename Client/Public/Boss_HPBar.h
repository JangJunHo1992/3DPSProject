#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CTexture;
class CVIBuffer_Rect;

END

BEGIN(Client)

class CBoss_HPBar final : public CGameObject
{
public:
	typedef struct tagBoss_HPBarDesc : public CGameObject::GAMEOBJECT_DESC
	{
		_float			fX, fY, fSizeX, fSizeY;
		_float			CurrentHP;
	}Boss_HPBar_DESC;

private:
	CBoss_HPBar(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CBoss_HPBar(const CBoss_HPBar& rhs);
	virtual ~CBoss_HPBar() = default;

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
	_float		m_fCurrentHP = 0.f;
	_float		m_fMaxHP = 500.f;
	_float      m_fRatio = 0.f;
	//_float		m_fDissolveWeight = { 0.f };
public:
	static	_bool		m_bCheckBossHPBar;
private:
	HRESULT Ready_Components(LEVEL eLevel);
	HRESULT Bind_ShaderResources();

	void Decrease_Ratio(_float fRatio);

public:
	/* 원형객체를 생성한다. */
	static CBoss_HPBar* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;
};

END

